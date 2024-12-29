grade = input()
total_grade = 0
total_credit = 0

grade_dict = {'A': 4, 'A-': 3.7,
         'B+': 3.3, 'B': 3, 'B-': 2.7,
         'C+': 2.3, 'C': 2, 'C-': 1.5,
         'D': 1.3, 'D-': 1,
         'F': 0}

while grade != '-1':
    credit = int(input())
    total_grade += grade_dict[grade] * credit
    total_credit += credit
    grade = input()

avg_grade = total_grade / total_credit
print("{:.2f}".format(avg_grade))