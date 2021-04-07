from turtle import speed,fd,lt,rt,goto,ht,up,down,speed,tracer
tracer(0,1)
def rysuj_trojkat(bok): 
    for k in range(3):
        fd(bok)
        lt(120)
up()
goto(-350, -250)
down()
def sierpinski(glebokosc, bok):
    rysuj_trojkat(bok)
    if glebokosc>0:
        sierpinski(glebokosc-1,bok/2)
        fd(bok/2)
        sierpinski(glebokosc-1,bok/2)
        lt(120)
        fd(bok/2)
        rt(120)
        sierpinski(glebokosc-1,bok/2)
        rt(120)
        fd(bok/2)
        lt(120)
ht()
sierpinski(7,500)
input()
