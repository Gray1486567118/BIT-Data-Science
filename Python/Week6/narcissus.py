def cube_sum(n):
    sum = 0
    while n > 0:
        sum += (n % 10) ** 3
        n = n // 10

    return sum


ls = []
for i in range(100, 1000):
    if i == cube_sum(i):
        ls.append(i)

for i in ls:
    if i != ls[-1]:
        print(i, end=', ')
    else:
        print(i, end='')