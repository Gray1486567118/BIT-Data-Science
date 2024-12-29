def add(n):
    sum = 0
    for i in range(1, n + 1):
        sum += i
    return sum

n = eval(input())
print(add(n))