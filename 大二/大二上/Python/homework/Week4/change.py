money = eval(input())

m50 = money // 50
money -= m50 * 50

m5 = money // 5
money -= m5 * 5

m1 = money // 1

print("50yuan：", m50)
print("5yuan：", m5)
print("1yuan：", m1)