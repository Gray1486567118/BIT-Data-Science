def prime(m):
    if m != int(m):
        m = int(m) + 1
    ls = []
    count = 0
    while count < 5:
        if is_prime(m):
            ls.append(m)
            count += 1
        m += 1
    for i in ls:
        last_ind = ls.__len__() - 1
        if i != ls[last_ind]:
            print(i, end=',')
        else:
            print(i)

def is_prime(m):
    if m == 1: return False
    if m == 2: return True
    for i in range(2, m):
        if m % i == 0:
            return False
    return True

n = eval(input())
prime(n)