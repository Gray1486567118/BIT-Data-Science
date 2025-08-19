import os
import re
import json
import ast
from sklearn.model_selection import train_test_split
from feature_eg import extract_section_features, extract_main_symptom_vector


# 全局映射表
SYNDROME_LIST = [
    '气虚血瘀证', '痰瘀互结证', '气阴两虚证', '气滞血瘀证',
    '肝阳上亢证', '阴虚阳亢证', '痰热蕴结证', '痰湿痹阻证',
    '阳虚水停证', '肝肾阴虚证'
]
DISEASE_LIST = ['胸痹心痛病', '心衰病', '眩晕病', '心悸病']
HERB_LIST = [] 


# 原始 & 目标文件路径
BASE_DIR = os.path.dirname(__file__)
RAW_DIR  = os.path.join(BASE_DIR, '..', 'data')
TRAIN_RAW = os.path.join(RAW_DIR, 'train_raw.json')
TRAIN_OUT   = os.path.join(RAW_DIR, 'train.json')
VAL_OUT     = os.path.join(RAW_DIR, 'val.json')
TV_OUT = os.path.join(RAW_DIR, 'train_val.json')  # 合并的训练验证集

TEST_RAW_IN = os.path.join(RAW_DIR, 'test_raw_input.json')
TEST_RAW_OUT = os.path.join(RAW_DIR, 'test_raw_output.json')
TEST_IN = os.path.join(RAW_DIR, 'test_input.json')
TEST_OUT = os.path.join(RAW_DIR, 'test_output.json')




# 需要拼接的字段 & 分隔符
FIELDS = ['性别', '年龄', '发病节气', '主诉', '症状', '中医望闻切诊', '病史']  # max_length=512
# FIELDS = ['性别', '年龄', '主诉', '症状', '中医望闻切诊', '病史', '体格检查', '辅助检查']  # max_length=512
# FIELDS = ['性别', '年龄', '主诉', '症状', '中医望闻切诊']  # max_length=256
SEP = '\n'

# 节气到季节的映射
SOLAR_TERM_TO_SEASON = {
    '立春': '春天', '雨水': '春天', '惊蛰': '春天', '春分': '春天', '清明': '春天', '谷雨': '春天',
    '立夏': '夏天', '小满': '夏天', '芒种': '夏天', '夏至': '夏天', '小暑': '夏天', '大暑': '夏天',
    '立秋': '秋天', '处暑': '秋天', '白露': '秋天', '秋分': '秋天', '寒露': '秋天', '霜降': '秋天',
    '立冬': '冬天', '小雪': '冬天', '大雪': '冬天', '冬至': '冬天', '小寒': '冬天', '大寒': '冬天'
}



# === 主处理函数 ===
def preprocess_train():
    """
    1) 读取原始训练集 
    2) 拼接文本
    3) 字符标签->索引,
    4) 划分 train/val
    5) 保存到 train.json & val.json
    """
    data = json.load(open(TRAIN_RAW, 'r', encoding='utf-8'))
    samples = []
    for item in data:
        # 1. 拼接指定字段
        parts = []
        for f in FIELDS:
            txt = item.get(f, '').strip()
            if txt:
                # 处理前缀
                if f == '发病节气':
                    # 将节气转换为季节
                    season = SOLAR_TERM_TO_SEASON.get(txt, txt)
                    txt = f'【发病季节】{season}'
                    parts.append(txt)
                else:
                    if f == '主诉' and txt.startswith('主  诉：'):
                        txt = txt[5:]
                    elif f == "中医望闻切诊" and txt.startswith('中医望闻切诊：'):
                        txt = txt[7:]
                    parts.append(f'【{f}】' + txt)

        full_text = SEP.join(parts)

        # 2. 证型多标签 -> 索引列表
        syndromes = [s for s in item['证型'].split('|') if s]
        syn_idx = [SYNDROME_LIST.index(s) for s in syndromes]
        # 3. 疾病单标签 -> 索引
        dis_idx = DISEASE_LIST.index(item['疾病'].strip())

        # 4. 抽取望闻切诊特征向量
        wmqz_text = item.get('中医望闻切诊', '')
        face_vec, tongue_vec, pulse_vec = extract_section_features(wmqz_text)

        # 5. 抽取主诉特征向量
        main_symptoms = item.get('主诉', '')
        main_symptoms_vec = extract_main_symptom_vector(main_symptoms)


        samples.append({"ID": item['ID'],
                        'text': full_text,
                        'syndrome': syn_idx,
                        'disease': dis_idx,
                        "face_vec": face_vec,
                        "tongue_vec": tongue_vec,
                        "pulse_vec": pulse_vec,
                        "main_symptoms": main_symptoms_vec})

    # 4. 划分 80% train, 20% val，保证疾病分布一致
    train, val = train_test_split(
        samples, test_size=0.2, random_state=42,
        stratify=[s['disease'] for s in samples]
    )

    # 5. 保存
    json.dump(train, open(TRAIN_OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)
    json.dump(val,   open(VAL_OUT,   'w', encoding='utf-8'), ensure_ascii=False, indent=2)
    print(f"Saved {len(train)} train samples and {len(val)} val samples.")


    # 如果需要合并训练和验证集，可以取消下面的注释, 注释掉4、5
    # json.dump(samples, open(TV_OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)


def preprocess_test():
    """
    1) 处理输入
    2) 处理输出
    """
    # 1. 处理输入
    data = json.load(open(TEST_RAW_IN, 'r', encoding='utf-8'))
    inputs = []
    for item in data:
        # 拼接指定字段
        parts = []
        for f in FIELDS:
            txt = item.get(f, '').strip()
            if txt:
                # 处理前缀
                if f == '发病节气':
                    # 将节气转换为季节
                    season = SOLAR_TERM_TO_SEASON.get(txt, txt)
                    txt = f'【发病季节】{season}'
                    parts.append(txt)
                else:
                    if f == '主诉' and txt.startswith('主  诉：'):
                        txt = txt[5:]
                    elif f == "中医望闻切诊" and txt.startswith('中医望闻切诊：'):
                        txt = txt[7:]
                    parts.append(f'【{f}】' + txt)
                    
        full_text = SEP.join(parts)

        # 抽取望闻切诊特征向量
        wmqz_text = item.get('中医望闻切诊', '')
        face_vec, tongue_vec, pulse_vec = extract_section_features(wmqz_text)

        # 抽取主诉特征向量
        main_symptoms = item.get('主诉', '')
        main_symptoms_vec = extract_main_symptom_vector(main_symptoms)

        inputs.append({"ID": item['ID'], 
                       'text': full_text,
                       "face_vec": face_vec,
                       "tongue_vec": tongue_vec,
                       "pulse_vec": pulse_vec,
                       "main_symptoms": main_symptoms_vec})

    # 保存处理后的输入
    json.dump(inputs, open(TEST_IN, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)
    print(f"Saved {len(inputs)} test inputs.")

    # 2. 处理输出
    data = json.load(open(TEST_RAW_OUT, 'r', encoding='utf-8'))
    outputs = []
    for item in data:
        # 证型多标签 -> 索引列表
        syndromes = [s for s in item['子任务1'][0].split('|') if s]
        syn_idx = [SYNDROME_LIST.index(s) for s in syndromes]

        # 疾病单标签 -> 索引
        dis_idx = DISEASE_LIST.index(item['子任务1'][1].strip())

        # 中药多标签 -> 索引列表
        herbs = [h for h in ast.literal_eval(item['子任务2']) if h]
        herb_idx = [HERB_LIST.index(h) for h in herbs]

        outputs.append({"ID": item['ID'],
                        'syndrome': syn_idx,
                        'disease': dis_idx,
                        'herb': herb_idx})
        
    # 保存处理后的输出
    json.dump(outputs, open(TEST_OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=2)
    print(f"Saved {len(outputs)} test outputs.")


def fill_herb_list():
    data = None
    with open(TEST_RAW_OUT, 'r', encoding='utf-8') as file:
        data = json.load(file)

    all_herbs = set()
    
    # 遍历数据列表
    for item in data:
        # 提取子任务2的值并转换为列表
        herbs = ast.literal_eval(item["子任务2"])
        # 将提取的中药列表添加到集合中
        all_herbs.update(herbs)

    global HERB_LIST
    HERB_LIST = sorted(list(all_herbs))



if __name__ == '__main__':
    fill_herb_list()
    preprocess_train()
    preprocess_test()