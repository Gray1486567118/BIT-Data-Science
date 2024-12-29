n = int(input())

ls = ['Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',  'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y']

def trans(n):
    if n <= 26:
        return ls[n % 26]
    if n % 26 == 0:
        return trans((n - 26) // 26) + ls[0]
    return trans(n // 26) + ls[n % 26]

print(trans(n))