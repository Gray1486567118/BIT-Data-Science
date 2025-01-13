def getNum():  # 获取用户不定长度的输入
    ls = input().split(',')
    for i in range(len(ls)):
        ls[i] = float(ls[i])
    ls = sorted(ls)
    return ls

def mean(numbers):  # 计算平均值
    return sum(numbers) / len(numbers)

def median(numbers):  # 计算中位数
    num = len(numbers)
    if num % 2 == 1:
        return numbers[num // 2]
    return (numbers[num // 2] +numbers[num // 2 - 1]) / 2


def dev(numbers, mean):  # 计算方差
    return sum((x - mean) ** 2 for x in numbers) / (len(numbers) - 1)


n = getNum()  # 主体函数
m = mean(n)
print("平均值:{:.2f},标准差:{:.2f},中位数:{}".format(m, dev(n, m) ** 0.5, int(median(n)) if int(median(n)) == median(n) else median(n)))