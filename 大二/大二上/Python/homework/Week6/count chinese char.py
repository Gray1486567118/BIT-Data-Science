s = input("")  # 输入包含中文的字符串：
count = 0
for c in s:
    uni = ord(c)
    if int('4E00', 16) <= uni <= int('9FA5', 16):
        count += 1
print(count)
