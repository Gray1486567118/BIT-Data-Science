m = set(input().split(' '))
n = set(input().split(' '))

new_set = (m | n) - (m & n)
ls = []
for item in new_set:
    ls.append(int(item))

ls = sorted(ls)
for item in ls:
    print(item)
