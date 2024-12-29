import math


def welcome():
    print("*" * 46)
    print("****      欢迎进入三角形面积计算程序      ****")
    print("*" * 46)
    print("1. 退出")
    print("2. 三角形面积（已知底边和高）")
    print("3. 三角形面积（已知两条边长以及夹角）")
    print("4. 三角形面积（已知三条边长）")

def triangle_area2(base, height):
    return 0.5 * base * height

def triangle_area3(a, b, gamma):
    return 0.5 * a * b * math.sin(math.radians(gamma))

def triangle_area4(a, b, c):
    s = (a + b + c) / 2
    return math.sqrt(s * (s - a) * (s - b) * (s - c))

welcome()

choice = choice = eval(input("choice:"))
while choice != 1:
    if choice == 2:
        base = eval(input("Base:"))
        height = eval(input("Height:"))
        area = triangle_area2(base, height)
    elif choice == 3:
        a = eval(input("A:"))
        b = eval(input("B:"))
        gamma = eval(input("Gamma:"))
        area = triangle_area3(a, b, gamma)
    elif choice == 4:
        a = eval(input("A:"))
        b = eval(input("B:"))
        c = eval(input("C:"))
        area = triangle_area4(a, b, c)
    print("The area is {}".format(area))
    choice = eval(input("choice:"))

print("Bye Bye!")
