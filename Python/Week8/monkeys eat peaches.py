def f(n):
    if n == 10:
        return 1
    return (f(n + 1) + 1) * 2

print(f(1))