import random as r

ls = input().split(',')
seed = int(ls[0]) + int(ls[1])
r.seed(seed)

str = ''
for i in range(20):
    str += chr(r.randint(32, 127))

print(str)