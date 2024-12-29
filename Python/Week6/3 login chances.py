error = 0

while error < 3:
    username = input()
    password = input()

    if username == 'Kate' and password == '666666':
        print("登录成功！")
        break
    else:
        error += 1
        if error == 3:
            print("3次用户名或者密码均有误！退出程序。")