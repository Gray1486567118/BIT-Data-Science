file = open('data.csv', 'r')

for line in file.readlines():
    cleared_line = line.split(' ')
    for i in cleared_line:
        print(i,end='')

file.close()