fruits = {"apple":10, "mango":12, "durian":20, "banana":5}
m = 'apple'

for key in fruits.keys():
    if fruits[key] > fruits[m]:
        m = key
print('{}:{}'.format(m,fruits[m]))