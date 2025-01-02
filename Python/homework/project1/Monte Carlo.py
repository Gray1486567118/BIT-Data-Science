import turtle as t
import random as r


def draw_square(side):
    side = side / 2
    move_to(-side, -side)
    t.setheading(90)
    t.pensize(4)

    for i in range(4):
        t.forward(side * 2)
        t.right(90)

def draw_circle(radius):
    move_to(radius, 0)
    t.pencolor("red")
    t.pensize(3)

    t.circle(radius)


def move_to(m, n):
    t.penup()
    t.goto(m, n)
    t.pendown()


# bg init
size = 200
t.speed(0)
t.hideturtle()

draw_square(size * 2)
draw_circle(size)

# random monte carlo
count = 0
dots = 1000
for i in range(dots):
    x = r.uniform(-size, size)
    y = r.uniform(-size, size)
    move_to(x, y)

    if x ** 2 + y ** 2 <= size ** 2:
        count += 1
        t.dot(5, "red")
    else:
        t.dot(5, "black")

pi = count / dots * 4
print("{:.6f}".format(pi))
t.done()
