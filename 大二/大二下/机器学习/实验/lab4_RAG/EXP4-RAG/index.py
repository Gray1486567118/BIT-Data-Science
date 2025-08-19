import os
import json
from NaiveRAG import NaiveRAG, LocalSentenceSplitter

def main():
    text_file = "./concatenated_paragraphs.txt"
    if not os.path.exists(text_file):
        print(f"未找到文件: {text_file}")

    # 读取 JSON 列表
    with open(text_file, "r", encoding="utf-8") as f:
        text_list = f.readlines()

    # 初始化自定义的 SentenceSplitter，设定 chunk_size 和 chunk_overlap
    splitter = LocalSentenceSplitter(chunk_size=512, chunk_overlap=128)

    rag = NaiveRAG(
        embedding_dim=1024,  # 视你的模型输出维度而定
        work_dir="./work_dir",
        model="bge-large"      # 你在本地 Ollama 中使用的模型名称
    )
    texts = []
    for i,item in enumerate(text_list):
        splitted_chunks = splitter.split_text(item)
        texts.extend(splitted_chunks)
        print(f"Travers {i} complete")
    print("Travers complete")
    print(f"Total wiki page number : {len(texts)}")
    rag.build_index(texts)
    print("Build index complete")

if __name__ == "__main__":
    main()