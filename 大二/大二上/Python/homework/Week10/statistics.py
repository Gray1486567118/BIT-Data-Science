import random as r

nums = input().split()
m, n = int(nums[0]), int(nums[1])
r.seed(10)

num_dict = {}
for _ in range(100):
    random_num = r.randint(m, n)
    num_dict[random_num] = num_dict.get(random_num, 0) + 1

ls = sorted(num_dict.items(), key = lambda x: x[0])
for item in ls:
    print("{} {}".format(item[0], item[1]))