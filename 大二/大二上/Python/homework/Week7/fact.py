n = eval(input())

def sum_fact(n):
    last = 1
    sum = 0
    for i in range(1, n + 1):
        last *= i
        sum += last
    return sum

print(sum_fact(n))