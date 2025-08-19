# 简单RAG实现 - 课程实验

一个简单的检索增强生成（RAG）系统实现，作为课程实验。学生需要完成缺失的代码组件，构建一个功能完整的RAG系统，能够使用检索到的文档片段回答问题。

## 概述

系统由三个主要组件组成：
- **文本分块**: `LocalSentenceSplitter` 用于将文档分割成可管理的文本块
- **向量存储**: `HNSWVectorStore` 使用HNSW算法进行高效的相似性搜索
- **RAG流水线**: 集成嵌入、检索和生成，实现问答功能

## 项目结构

```
├── NaiveRAG.py          # 主要RAG实现（未完成）
├── E2E_eval.py          # 端到端评估脚本
├── index.py             # 索引构建脚本
├── llm_client.py        # LLM客户端（未提供）
├── concatenated_paragraphs.txt  # 源文本数据
├── musique_dev.jsonl    # 评估数据集
└── work_dir/            # 索引和日志的工作目录
```

## 环境要求

开始前，请确保：

1. **Ollama** 已安装并在 `localhost:11434` 上运行
2. **BGE-Large嵌入模型** 在Ollama中可用
3. 安装必需的Python包：
   ```bash
   pip install hnswlib numpy requests
   ```

## 基础任务（必做）

### 1. 完善LocalSentenceSplitter（文本分块）

**文件**: `NaiveRAG.py`, 类 `LocalSentenceSplitter`

**任务**:

- 实现 `_zng_new()` 方法进行句子分割
- 完成 `split_text()` 方法，实现正确的分块逻辑
- 确保文本块之间的重叠处理正确

**关键要求**:

- 遵守 `chunk_size` 参数
- 正确实现 `chunk_overlap`
- 处理文本边界的边缘情况

### 2. 完善HNSWVectorStore（向量索引）

**文件**: `NaiveRAG.py`, 类 `HNSWVectorStore`

**任务**:
- 在 `__init__()` 方法中实现索引加载
- 实现新索引的初始化
- 确保向量存储和检索的正确性

**关键要求**:
- 使用余弦相似度作为距离度量
- 处理新索引创建和现有索引加载
- 保持向量和文本标签之间的一致性

### 3. 增强提示工程，端到端eval

**文件**: `NaiveRAG.py，E2E_eval.py`, 变量 `naive_prompt`

**任务**:
- 改进提示模板以获得更好的LLM响应
- 确保答案用 `{}` 大括号包裹以便评估
- 针对MuSiQue数据集优化提示结构
- 执行`E2E_eval.py`，获得前100个问题的回答正确率

**关键要求**:
- 清晰的指令格式
- 正确的上下文集成
- 一致的答案格式

## 加分任务（每项1分）

### 1. 分块策略探索

实验不同的分块方法：
- **可变分块大小**: 测试不同的 `chunk_size` 值（128, 256, 512, 1024）
- **可变重叠**: 实验不同的 `chunk_overlap` 比例（0%, 25%, 50%）
- **替代分块方法**: 实现语义或段落级别的分块

### 2. 查询重写

**文件**: `E2E_eval.py`, 函数 `rewrite_query()`

实现查询增强技术：
- **查询分解**: 将复杂问题分解为简单的子问题
- **语义对齐**: 将问题转换为匹配段落风格（参考 [HyDE](https://arxiv.org/pdf/2212.10496) 论文）
- **查询扩展**: 添加相关术语或上下文

### 3. 其他改进

实现任何能提高P/R/F1指标的方法：
- **重排序器**: 在 `generate_prompt()` 方法中添加重排序步骤
- **多向量检索**: 检索更多候选项并过滤
- **混合搜索**: 结合密集和稀疏检索

## 使用说明

### 步骤1: 构建索引

```bash
python index.py
```

此脚本将：
- 从 `concatenated_paragraphs.txt` 读取文本数据
- 使用 `LocalSentenceSplitter` 将文本分割成块
- 使用本地Ollama生成嵌入
- 构建并保存HNSW索引

### 步骤2: 运行评估

```bash
python E2E_eval.py
```

此脚本将：
- 从 `musique_dev.jsonl` 加载前100个问题
- 对每个问题执行检索增强生成
- 计算精确率、召回率和F1分数
- 显示结果和指标

## 评估指标

系统使用以下指标评估：
- **精确率（Precision）**: 正确答案数 / 预测答案总数
- **召回率（Recall）**: 正确答案数 / 相关答案总数
- **F1分数**: 精确率和召回率的调和平均数

## 实现注意事项

### 需要完成的组件

1. **文本分割逻辑**: 
   - 句子边界检测
   - 分块大小管理
   - 重叠计算

2. **向量索引管理**:
   - HNSW索引初始化
   - 索引持久化和加载
   - 相似性搜索实现

3. **提示工程**:
   - 上下文格式化
   - 答案结构指导
   - 响应解析兼容性

### API密钥配置

记住在 `E2E_eval.py` 中将 `"your api key here"` 替换为实际LLM API密钥。


## 数据集说明

### MuSiQue数据集
- **类型**: 多跳问答数据集
- **格式**: JSONL格式，每行一个JSON对象
- **字段**:
  - `question`: 问题文本
  - `answer`: 标准答案
  - `answer_aliases`: 答案的别名列表
  - `context`: 相关上下文（本次实验中未使用）

### 文本语料
- **文件**: `concatenated_paragraphs.txt`
- **格式**: 每行一个段落
- **用途**: 用于构建检索索引的知识库
