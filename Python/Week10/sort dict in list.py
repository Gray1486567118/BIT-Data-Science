n = int(input())

ls = []

for _ in range(n):
    s = input()
    s = s.split()
    new = {'name': s[0], 'age': int(s[1])}
    ls.append(new)

age_sorted = sorted(ls, key = lambda x: x['age'])
print(age_sorted)

name_sorted = sorted(ls, key = lambda x: x['name'])
print(name_sorted)