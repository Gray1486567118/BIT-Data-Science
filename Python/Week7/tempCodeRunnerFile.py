def is_leap(year):
    """判断year是否为闰年，闰年返回True，非闰年返回False"""
    if year % 400 == 0: return True
    if year % 100 == 0: return False
    if year % 4 == 0: return True


def days_of_month(date_str):
    """根据输入的年月日，返回该月的天数"""
    dic = {'01': 31, '02': 28, '03': 31, '04': 30, '05': 31, '06': 30,
           '07': 31, '08': 31, '09': 30, '10': 31, '11': 30, '12': 31}
    year = date_str[:4]
    month = date_str[5:7]
    if is_leap(int(year)) and month == '02':
        return 29
    return dic[month]