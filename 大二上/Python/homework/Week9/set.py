# num of operands
n = int(input())

# init set
cities = set(input().split(" "))

# operating
for _ in range(n):
    op = input().split(" ")
    if op[0] == 'print':
        ls = list(cities)
        ls = sorted(ls)
        print(ls)
    elif op[0] == 'add':
        cities.add(op[1])
    elif op[0] == 'del':
        cities.discard(op[1])
    elif op[0] == 'clear':
        cities.clear()
    elif op[0] == 'update':
        for i in range(1, len(op)):
            cities.add(op[i])