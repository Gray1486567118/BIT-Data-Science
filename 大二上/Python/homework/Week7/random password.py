import random

def genpwd(length):
    password = random.randint(10 ** (length - 1), 10 ** length - 1)
    return password

length = eval(input())
random.seed(17)
for i in range(3):
    print(genpwd(length))
