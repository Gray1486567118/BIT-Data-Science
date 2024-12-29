n = int(input())
ls = []

def defactor(n):
    while n > 1:
        for i in range(2, n + 1):
            if n % i == 0:
                ls.append(i)
                n //= i
                break

defactor(n)
print(ls)