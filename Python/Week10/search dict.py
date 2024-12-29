dict1 = {'赵广辉':'13299887777','特朗普':'814666888','普京':'522888666','吴京':'13999887777'}

name = input()

try:
    print(name + ":" + dict1[name])
except:
    print("数据不存在")