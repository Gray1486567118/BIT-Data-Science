def is_prime(n):
    """判断素数的函数,接收一个正整数为参数，参数是素数时返回True，否则返回False。减小判定区间，减少循环次数，提升效率"""
    if n < 2: return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


def is_plalindrome(n):
    s = str(n)
    return s == s[::-1]

def reverse_is_prime(n):
    n = int(str(n)[::-1])
    return is_prime(n)

def reverse_prime(number):
    """接收一个正整数参数，找出并在同一行内输出所有小于number的反素数，每个数字后一个空格。
    反素数指某数i及其逆序数都是素数，但数i对应的字符串不是回文字符串。函数无返回值"""
    for i in range(13, number):
        if is_prime(i) and not is_plalindrome(i) and reverse_is_prime(i):
            print(i, end=' ')


positive_int = int(input())
reverse_prime(positive_int)
