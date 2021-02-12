from turtle import fd, rt, ht, lt, filling, begin_fill, end_fill, speed, fillcolor, color
from random import randint, random

speed('fastest')
ht()
def kwadrat(k):
    fillcolor(random(),random(),random())
    begin_fill()
    for _ in range(4):
        fd(k)
        rt(90)
    end_fill()
    fd(k)

def piramida(n, k):
    wysokosc_temp = n
    while(wysokosc_temp > 1):
        for i in range(wysokosc_temp):
            kwadrat(k)
        rt(180)
        fd(wysokosc_temp * k)
        wysokosc_temp -= 1
        rt(180)
        fd(k / 2)
        lt(90)
        fd(k)
        rt(90)
    if(wysokosc_temp == 1):
        for i in range(wysokosc_temp):
            kwadrat(k)


piramida(7, 50)
input()