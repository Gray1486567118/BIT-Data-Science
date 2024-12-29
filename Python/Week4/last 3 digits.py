n = eval(input())

last_3_digit = pow(2, n)

if last_3_digit < 1000:
    print(last_3_digit)
else:
    last_3_digit %= 1000
    print(f"{last_3_digit:03}")