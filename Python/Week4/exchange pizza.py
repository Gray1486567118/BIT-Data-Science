import math

m = eval(input())
n = eval(input())


def diameter(len):
    len = len * 2.54
    return round(len, 0)


def ratio(d1, d2):
    return d1 * d1 / (d2 * d2)


m = diameter(m)
n = diameter(n)

num = math.ceil(ratio(m, n))
print(num)
