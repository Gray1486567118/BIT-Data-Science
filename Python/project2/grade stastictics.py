import pandas as pd

# 读取数据
path = '期末考试成绩统计.xlsx'
score_data = pd.read_excel(path, sheet_name=None)

# 初始化DataFrame，用于存储每个学生的学号、姓名及总分
student_scores = pd.DataFrame()

# 遍历成绩表，将学号、姓名和成绩合并到一个DataFrame中
for sheet_name, data in score_data.items():
    print(sheet_name)
    print(data)
    if student_scores.empty:
        # 空表则先初始化
        student_scores = data[['学号', '姓名', '成绩']]
    else:
        # 非空则合并数据
        student_scores = pd.merge(student_scores, data[['学号', '成绩']], on='学号', how='left')
    # 重命名成绩列
    student_scores = student_scores.rename(columns={'成绩': sheet_name})

# 计算总分
student_scores['总分'] = student_scores.iloc[:, 2:].sum(axis=1)

# 按总分降序排名，若总分相同则按学号升序
student_scores = student_scores.sort_values(by=['总分', '学号'], ascending=[False, True]).reset_index(drop=True)

# 为每个学生分配排名（相同总分相同排名）
student_scores['排名'] = student_scores['总分'].rank(method='min', ascending=False).astype(int)

# 提取输出列
result = student_scores[['排名', '学号', '姓名', '总分']]
print(result)

# 保存到result.csv文件中
result.to_csv('result.csv', index=False)
