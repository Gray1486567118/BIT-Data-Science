import json
import re
from collections import defaultdict

# 定义你要统计的字段
fields = {
    "主诉症状": [],
    "面色": [],
    "气息": [],
    "舌色": [],
    "舌苔": [],
    "脉象": []
}

# 构建匹配规则
def extract_main_complaints(text):
    return re.findall(r"[，,、。；]*?([胸痛|胸闷|咳嗽|头晕|黑便|心悸|腹泻|乏力|便秘|失眠|咳痰|气短]+)", text)

def extract_appearance(text):
    res = {}
    if "面色" in text:
        res["面色"] = re.findall(r"面色(.*?)，", text)
    if "气息" in text:
        res["气息"] = re.findall(r"气息(.*?)[，。；]", text)
    if "舌" in text:
        res["舌色"] = re.findall(r"舌([红淡暗紫][^\s，、。]*)", text)
        res["舌苔"] = re.findall(r"苔([^\s，、。]*)", text)
    if "脉" in text:
        res["脉象"] = re.findall(r"脉([滑弦细沉数迟虚实][^\s，、。]*)", text)
    return res

# 初始化统计器
stats = defaultdict(set)

with open('./data/train_raw.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

for item in data:
    # 提取主诉
    # main = item.get("主诉", "")
    # complaints = extract_main_complaints(main)
    # stats["主诉症状"].update(complaints)

    # 提取中医望闻切诊
    diag = item.get("中医望闻切诊", "")
    diag_info = extract_appearance(diag)
    for key, values in diag_info.items():
        for val in values:
            stats[key].add(val)

# 输出结果
for k, v in stats.items():
    print(f"{k}（共{len(v)}种）：")
    for vi in sorted(v):
        print(f"  - {vi}")
    print()


