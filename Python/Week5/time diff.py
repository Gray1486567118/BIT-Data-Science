import time as t

time_input = input()
time1, time2 = time_input.split(",")

t1 = t.strptime(time1, "%Y年%m月%d日%H点%M分%S秒")
t2 = t.strptime(time2, "%Y年%m月%d日%H点%M分%S秒")

diff = (int(t.mktime(t2)) - int(t.mktime(t1))) // 86400
print(diff)