import random as rd

m = int(input())
n = int(input())
rd.seed(m)

ls = []
for _ in range(n):
    ls.append(str(rd.randint(0, 9)))

print(ls)
ls = sorted(list(set(ls)))
print(ls)