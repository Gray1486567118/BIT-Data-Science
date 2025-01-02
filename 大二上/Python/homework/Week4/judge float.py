try:
    s = eval(input())
    if type(s) == float:
        print("True")
    else:
        print("False")
except SyntaxError:
    print("True")
