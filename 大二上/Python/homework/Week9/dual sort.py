import random as rd

rd.seed(int(input()))
ls = []
for _ in range(10):
    ls.append(rd.randint(-100, 100))

ls.sort(key=lambda x: 100 - x if x >= 0 else x + 200)
print(ls)