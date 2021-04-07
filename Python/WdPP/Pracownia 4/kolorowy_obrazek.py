from turtle import fd, rt, lt, speed, ht, fillcolor, begin_fill, end_fill

speed('fastest')
def kolorowe_kolko(n, k):
    kolorowy_licznik = k - 1
    d = n + k * 10
    for i in range(k):
        if kolorowy_licznik % 3 == 0: 
            fillcolor('yellow')
        if kolorowy_licznik % 3 == 1                                                                                                                                                                                                            : 
            fillcolor('#6666ff')
        if kolorowy_licznik % 3 == 2: 
            fillcolor('green')
        begin_fill()
        for i in range(180):
            fd((3.14 * 2 * d / 180))
            rt(2)
        end_fill()
        d -= 10
        kolorowy_licznik -= 1


kolorowe_kolko(40, 13)
input()