x = eval(input())

result = 0

for i in range(1, x + 1):
    result += pow(1 + 1 / i, i)

print("{:.8f}".format(result))