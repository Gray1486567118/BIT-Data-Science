import math
def sqrt_binary(num):
    low = 0
    high = num
    mid = (low + high) / 2
    while abs(mid * mid - num) > 1e-6:        
        if mid * mid < num:
            low = mid
        else:
            high = mid
        mid = (low + high) / 2
    return mid

			
num = float(input())
print(sqrt_binary(num))
print(math.sqrt(num))