f = open("sensor-data-1k.txt", "r")

total_light = 0
for line in f.readlines():
    curr_line = line.split()
    total_light += float(curr_line[4])

avg = total_light / 1000

print("{:.2f}".format(avg))

f.close()