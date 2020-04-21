from turtle import *
def writewords():
    up()
    goto(-100,50)
    down()
    color('red')
    write("To My Lover",move=True,align="left",font=("仿宋",20,"normal"))
def heart(x):
    pensize(2)
    color('red','pink')
    up()
    goto(0,-100)
    down()
    begin_fill()
    left(45)
    speed(1)
    forward(2*x)
    circle(1*x,180)
    right(90)
    circle(1*x,180)
    forward(2*x)
    end_fill()
for i in range(10,100,10):
    heart(i)
writewords()
    
