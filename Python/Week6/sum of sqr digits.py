n = eval(input())

sum = 0
while n > 0:
    sum += (n % 10) ** 2
    n = n // 10

print(sum)
