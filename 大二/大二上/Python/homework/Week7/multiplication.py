def cmul(*n):
    result = 1
    for i in n:
        result *= i
    return result

print(eval("cmul({})".format(input())))