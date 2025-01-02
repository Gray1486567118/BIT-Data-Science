def f(m,n):
    #定义函数体完成题目要求功能
    for i in m:
        if i not in n:
            return False
    return True


def all_alpha(s):
    return all(c.isalpha() for c in s)


m = input()
if all_alpha(m):    #完成该条件分支，输入字符串n判断单词m是否可以由n中的某些字符组成
    n = input()
    if f(m, n):
        print('FOUND')
    else:
        print('NOT FOUND')
else:
    print('ERROR')