s = input()

set_s = set(s)

ls = sorted(list(set_s))
for char in ls:
    print(char, end='')