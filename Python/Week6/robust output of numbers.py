try:
    n = input()

    if 'j' in n:
        n = complex(n)
    else:
        n = float(n)
        if n == int(n):
            n = int(n)
    print(n * n)
except ValueError:
    print("输入有误")
