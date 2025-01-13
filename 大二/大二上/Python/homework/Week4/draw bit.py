import turtle

# 创建 turtle 对象
pen = turtle.Turtle()
pen.speed(3)

# 定义画笔移动函数


def move_pen(x, y):
    pen.penup()
    pen.goto(x, y)
    pen.pendown()


def draw_b():
    pen.setheading(90)  # 朝上
    pen.forward(100)    # 画竖线
    pen.right(90)

    pen.forward(10)
    pen.circle(-25, 180)
    pen.forward(10)

    pen.left(180)

    pen.forward(15)
    pen.circle(-25, 180)
    pen.forward(15)


def draw_i():
    pen.setheading(0)
    pen.forward(30)

    pen.left(180)
    pen.forward(15)

    pen.right(90)
    pen.forward(100)

    pen.left(90)
    pen.forward(15)

    pen.left(180)
    pen.forward(30)


def draw_t():
    pen.setheading(0)
    pen.forward(50)

    pen.backward(25)
    pen.right(90)
    pen.forward(100)


move_pen(-150, 0)
draw_b()

move_pen(-50, 0)
draw_i()

move_pen(50, 100)
draw_t()

# 隐藏画笔并完成
pen.hideturtle()
turtle.done()
