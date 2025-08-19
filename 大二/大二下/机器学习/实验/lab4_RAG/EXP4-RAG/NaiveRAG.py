import os
import requests
import hnswlib
import numpy as np
from typing import List, Tuple
import re
import json


#TODO: 添加prompt，确保回答被{}包裹
#TODO：加分项，修改prompt，思考怎么样LLM更容易正确回答
naive_prompt = """
----Role----
You are an intelligent language model designed to answer questions based strictly on provided Wikipedia texts and general world knowledge only when necessary.

----Instructions----
- Use ONLY the provided context texts below to answer the question.
- If the answer is not explicitly found in the context, say: {Not found in context}.
- Your response must be concise and fit within curly brackets, e.g., {your answer here}.
- Do NOT include any explanation, reasoning, or extra text—only the answer in brackets.

----Context----
{retrieved_documents}

----Question----
{user_question}

----Answer----
"""



class LocalSentenceSplitter:
    def __init__(self, chunk_size, chunk_overlap) -> None:
        self.chunk_size = chunk_size
        self.chunk_overlap = chunk_overlap

    @staticmethod
    def _zng(paragraph):
        pattern = u'([！？。…!?.\n])'
        return [sent for sent in re.split(pattern, paragraph, flags=re.U)]

    @staticmethod
    def _zng_new(paragraph):
        sentence = []
        #TODO: 添加split方法
        # 使用自己的方法来分割句子
        # import nltk
        # nltk.download('punkt')
        # from nltk.tokenize import sent_tokenize

        # sentence = sent_tokenize(paragraph)

        pattern = u'([！？。…!?.\n])'
        segs = re.split(pattern, paragraph)
        result = []
        for i in range(0, len(segs)-1, 2):
            sentence = segs[i].strip()
            punct = segs[i+1].strip()
            if sentence or punct:
                result.append(sentence + punct)
        if len(segs) % 2 != 0:
            last = segs[-1].strip()
            if last:
                result.append(last)
        return sentence

    def split_text(self, segment):
        chunks, chunk_now, size_now = [], [], 0
        no_left = False
        for s in LocalSentenceSplitter._zng_new(segment):
            #TODO: 添加chunk_now的判断，如果chunk_now的长度大于chunk_size，则进行分割
            # 额外需要确保正确overlap
            s = s.strip()
            if not s:
                continue

            chunk_now.append(s)
            size_now += len(s)

            if size_now >= self.chunk_size:
                chunks.append(" ".join(chunk_now))
                
                overlap, overlap_size = self._get_overlap(chunk_now)
                chunk_now = overlap
                size_now = overlap_size
        
        if chunk_now:
            chunks.append(" ".join(chunk_now))
                
        return chunks

    def _get_overlap(self, chunk):
        rchunk = chunk[:]
        rchunk.reverse()
        size_now, overlap = 0, []
        for s in rchunk[:-1]:
            overlap.append(s)
            size_now += len(s)
            if size_now > self.chunk_overlap:
                break
        overlap.reverse()
        return overlap, size_now

class OllamaEmbedding:
    """
    调用本地 Ollama 的 /embeddings 接口来获取文本的Embedding。
    假设 Ollama 版本支持 embeddings 功能，且在 localhost:11434 端口提供服务。
    你可以根据需要修改 URL、超时、模型名称等。
    """
    def __init__(self, host="http://localhost:11434", model="bge-large", work_dir="work_dir"):
        self.host = host
        self.model = model
        self.work_dir = work_dir
        # 日志文件，可在此记录一些embedding的调用信息
        self.log_path = os.path.join(self.work_dir, "logs.txt")
        os.makedirs(self.work_dir, exist_ok=True)

    def _log(self, msg: str):
        with open(self.log_path, "a", encoding="utf-8") as f:
            f.write(msg + "\n")

    def encode(self, texts: List[str]) -> np.ndarray:
        """
        输入若干文本，返回它们的向量（shape=[len(texts), dim]）。
        """
        embeddings = []
        for text in texts:
            try:
                payload = {
                    "model": self.model,
                    "prompt": text
                }
                # Ollama 的 /embeddings 接口（注意版本不同，接口可能略有差异）
                url = f"{self.host}/api/embeddings"
                r = requests.post(url, json=payload, timeout=60)
                r.raise_for_status()
                data = r.json()
                # data 应该包含 "embedding" 字段，这里做个简单取值
                emb = data.get("embedding", [])
                embeddings.append(emb)
                self._log(f"[encode] success for text: {text[:30]}..., embedding dim={len(emb)}")
            except Exception as e:
                # 异常时可记录日志，返回一个零向量或者直接抛出
                self._log(f"[encode] error for text: {text[:30]}..., error={e}")
                # 这里简单用全0向量顶替
                embeddings.append([0.0]*1024)  
        return np.array(embeddings)


class HNSWVectorStore:
    """
    用 hnswlib 来管理向量索引。采用 'cosine' 作为距离度量。
    """
    def __init__(self, embedding_dim: int, work_dir: str = "work_dir"):
        self.embedding_dim = embedding_dim
        self.work_dir = work_dir
        os.makedirs(self.work_dir, exist_ok=True)

        # index.bin是hnswlib的索引文件，labels.npy是文本的label
        self.index_path = os.path.join(self.work_dir, "index.bin")
        self.labels_path = os.path.join(self.work_dir, "labels.npy")

        # 判断索引文件是否已经存在，决定是加载还是新建
        if os.path.exists(self.index_path) and os.path.exists(self.labels_path):
            #TODO: 添加加载方法
            self.index = hnswlib.Index(space='cosine', dim=self.embedding_dim)
            self.index.load_index(self.index_path)
            self.labels = np.load(self.labels_path, allow_pickle=True).tolist()
            print("[HNSWVectorStore] index loaded from disk.")
            
        else:
            #TODO: 添加初始化方法
            self.index = hnswlib.Index(space='cosine', dim=self.embedding_dim)
            self.index.init_index(max_elements=10000, ef_construction=200, M=16)
            self.index.set_ef(50)  # 影响查询精度
            self.labels = []
            print("[HNSWVectorStore] created new empty index.")

    def add_texts(self, texts: List[str], embeddings: np.ndarray):
        """
        将文本和其向量插入 HNSW 索引，并记录 labels（即文本内容）。
        """
        num_new = embeddings.shape[0]
        start_id = len(self.labels)
        ids = np.arange(start_id, start_id + num_new)

        # 插入向量
        self.index.add_items(embeddings, ids)
        # 记录文本，以便检索时能得到对应的文本
        self.labels.extend(texts)

    def save(self):
        """
        将索引和对应 labels 保存到磁盘。
        """
        self.index.save_index(self.index_path)
        np.save(self.labels_path, np.array(self.labels, dtype=object), allow_pickle=True)
        print("[HNSWVectorStore] index saved.")

    def similarity_search(self, query_embedding: np.ndarray, top_k: int = 3) -> List[str]:
        """
        基于向量检索最相似的 Top-K 文本。
        """
        # hnswlib 返回的是 (ids, distances)
        ids, distances = self.index.knn_query(query_embedding, k=top_k)
        # ids shape: (1, top_k)   distances shape: (1, top_k)
        # 这里假设只有一个查询向量，所以取 ids[0]
        print(ids)   
        result_texts = [self.labels[idx] for idx in ids[0]]
        return result_texts


class NaiveRAG:
    """
    一个简易的RAG示例：用本地 Ollama 生成Embedding，再用HNSW检索相似文本，最后拼接回答。
    """
    def __init__(self, embedding_dim: int = 1024, work_dir="work_dir", model="bge-large"):
        self.work_dir = work_dir
        self.embedding_model = OllamaEmbedding(
            host="http://localhost:11434",
            model=model,
            work_dir=work_dir
        )
        self.vector_store = HNSWVectorStore(embedding_dim=embedding_dim, work_dir=work_dir)

    def build_index(self, text_chunks: List[str]):
        """
        对text_chunks做embedding并插入索引，然后保存索引到磁盘。
        """
        embeddings = self.embedding_model.encode(text_chunks)  # [N, dim]
        self.vector_store.add_texts(text_chunks, embeddings)
        self.vector_store.save()

    def generate_prompt(self, query: str, top_k: int = 3) -> str:
        """
        对用户query做embedding，然后从索引中检索top_k文本块，用简单方式拼接。
        """
        query_emb = self.embedding_model.encode([query])[0]  # shape=[dim]
        retrieved_texts = self.vector_store.similarity_search(query_emb, top_k=top_k)

        #TODO：加分项添加reranker，对retrieved_texts进行rerank
        #print(retrieved_texts)
        # 这里仅用一个很简单的拼接回答示例
        retrieved_texts = self.rerank(query_emb, retrieved_texts)
        context = "\n".join(retrieved_texts)
        #answer = (
        #    f"You are a helpful assistant please answer the question {query} with given context:\n{context}"
        #)
        prompt = naive_prompt+f"Q:{query}\ntexts:{context}\nA:"
        return prompt

    def rerank(self, query_emb, retrieved_texts: List[str]) -> List[str]:
        retrieved_embs = self.embedding_model.encode(retrieved_texts)
        scores = np.dot(retrieved_embs, query_emb)
        ranked = sorted(zip(scores, retrieved_texts), key=lambda x: -x[0])
        return [text for score, text in ranked]