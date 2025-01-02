s = input("")#输入一个字符串
ls = []
for c in s:
    ls.append(str(ord(c)))
print(','.join(ls))