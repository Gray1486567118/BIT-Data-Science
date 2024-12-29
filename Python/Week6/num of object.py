n = eval(input())

for i in range(n + 1):
    if i % 3 == 2 and i % 5 == 3 and i % 7 == 2:
        print(i)