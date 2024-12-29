def is_prime(n):
    """判断素数的函数,接收一个正整数为参数，参数是素数时返回True，否则返回False。减小判定区间，减少循环次数，提升效率"""
    if n < 2: return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

n = int(input())

if n % 2 == 1:
    print("Data error!")
else:
    for i in range(2, n // 2 + 1):
        if is_prime(i) and is_prime(n - i):
            print(n, "=", i, "+", n - i)
            break