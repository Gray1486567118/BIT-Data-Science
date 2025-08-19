import re

FACE_KEYWORDS = ["红", "黄", "白", "黑", "青", "暗"]
TONGUE_KEYWORDS = ["厚", "薄", "腻", "滑", "黄", "白", "红", "少"]
PULSE_KEYWORDS = ["细", "弦", "浮", "沉", "结", "代", "涩", "数", "缓", "迟", "滑", "弱", "紧", "濡", "枯", "实"]

FACE_SYNONYMS = {
    "暗": "暗",
    "黯": "暗",
    "少华": "暗",
    "无华": "暗",
    "欠润": "暗"
}

# 主诉归一标签
main_symptom_dict = {
    "心慌": ["心慌"],
    "心悸": ["心悸"],
    "心前区疼痛": ["心前区疼痛", "心前区灼烧感", "胸痛", "胸部隐痛", "心前区不适"],
    "心动过缓": ["心动过缓"],

    "乏力": ["乏力"],

    "胸闷": ["胸闷", "气短", "短气", "憋喘", "憋气", "憋闷"],
    "后背疼痛": ["后背胀痛", "后背疼痛"],
    "颈部疼痛": ["颈部疼痛"],
    "黑便": ["黑便"],
    "胁下疼痛": ["胁下疼痛"],

    "头晕": ["头晕", "头昏沉"],
    "头胀": ["头胀"],
    "头痛": ["头痛"],
    "恶心": ["恶心", "呕吐"],

    "高血压": ["血压升高", "高血压", "血压控制不佳"],
    "高血糖": ["血糖升高"],

    "水肿": ["水肿"],
    "眩晕": ["眩晕"],
    "晕厥": ["晕厥"],

    "视力模糊": ["失明", "视力模糊", "视物模糊"],
    "耳鸣": ["耳鸣"],
    "腰痛": ["腰痛"],
    "言语不利": ["言语不利"],
    "脸部麻木": ["脸部发麻", "脸部麻木"],
    "肢体麻木": ["四肢麻木", "肢体麻木"],
    "活动不利": ["活动不利"],
    "咳嗽": ["咳嗽"],
    "发热": ["发热"],
    "失眠": ["失眠"],
    "多汗": ["汗出", "多汗"],
    "怕冷": ["怕冷"],
    "口干": ["口干"],
    "口苦": ["口苦"]
}

MAIN_SYMPTOM_TAGS = list(main_symptom_dict.keys())  # 确保顺序一致



# === 特征抽取函数 ===
def normalize_face(word):
    return FACE_SYNONYMS.get(word, word)

def extract_section_features(text):
    clauses = re.split(r"[，、。；]", text)

    face_set, tongue_set, pulse_set = set(), set(), set()
    for clause in clauses:
        if "面色" in clause:
            for word in FACE_KEYWORDS + list(FACE_SYNONYMS.keys()):
                if word in clause:
                    face_set.add(normalize_face(word))
        elif "苔" in clause:
            for word in TONGUE_KEYWORDS:
                if word in clause:
                    tongue_set.add(word)
        elif "脉" in clause:
            for word in PULSE_KEYWORDS:
                if word in clause:
                    pulse_set.add(word)

    face_vec = [1 if k in face_set else 0 for k in FACE_KEYWORDS]
    tongue_vec = [1 if k in tongue_set else 0 for k in TONGUE_KEYWORDS]
    pulse_vec = [1 if k in pulse_set else 0 for k in PULSE_KEYWORDS]

    return face_vec, tongue_vec, pulse_vec


def extract_main_symptom_vector(text):
    """
    根据主诉映射字典抽取症状并返回多热编码向量。
    
    参数:
        text (str): 待处理文本
        mapping_dict (dict): 标签到同义词的映射字典，如 {"头晕": ["头晕", "头昏沉"]}
        
    返回:
        vector (List[int]): 多热向量（与 mapping_dict 的 key 顺序一致）
    """
    tag_list = list(main_symptom_dict.keys())
    tag_index = {tag: i for i, tag in enumerate(tag_list)}
    vec = [0] * len(tag_list)

    for tag, variants in main_symptom_dict.items():
        for variant in variants:
            if variant in text:
                vec[tag_index[tag]] = 1
                break  # 一旦匹配即跳出该组
    return vec