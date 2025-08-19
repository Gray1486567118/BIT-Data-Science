#!/bin/bash

# 安装 requirements.txt 中的依赖
pip install -r requirements.txt

# 设置环境变量
export HF_ENDPOINT=https://hf-mirror.com

# 下载模型
huggingface-cli download --resume-download Qwen/Qwen2.5-0.5B-Instruct --local-dir Qwen2.5-0.5B