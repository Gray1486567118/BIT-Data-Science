# 提示：递归函数调用
def defactor(N):  # 定义一个函数名称为defactor，意义是返回N的所有因子
    for i in range(2, N):  # 从2开始试试
        if N % i == 0:  # 如果试到 i 是 N 的因子的话，就返回i的所有因子和N/i的所有因子 的列表
            return [i] + defactor(N // i)  # 拼接 列表 + 列表，例如[2]+[3] 结果为[2, 3]
    # 如果没有试到就说明这个N是一个质数，就直接包含它的 列表
    return [N]  # 返回列表

if __name__ == '__main__':
    n = int(input())
    if n == 1:
        print([1])
    else:
        print(defactor(n))