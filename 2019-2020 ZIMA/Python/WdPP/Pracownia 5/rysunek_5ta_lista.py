from turtle import fd, ht, rt, lt, speed

speed('fastest')
tracer(0,1)
def rysunek(k):
    n = k
    rt(60)
    for i in range(6):
        while(n>0):
            for i in range(4):
                fd(n)
                lt(90)
            lt(90)
            fd(n)
            rt(90)
            fd(5)
            n -= 10
        fd(5)
        while(n<k):
            n += 10
            rt(90)
            fd(n)
            lt(90)
            if n<=k-10:
                fd(5)
        rt(60)
rysunek(50)
input()