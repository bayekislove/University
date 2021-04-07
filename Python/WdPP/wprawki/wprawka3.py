from turtle import fd, rt, up, down, ht, lt

def convert(n):
    tab = list(str(bin(n)))
    sama_liczba = tab[2:]
    return sama_liczba

def skocz():
    up()
    fd(40)
    down()


def rysuj_kreske():
    lt(90)
    fd(100)
    rt(180)
    fd(100)
    lt(90)

def rysuj_prostokacik():
    fd(70)
    lt(90)
    fd(100)
    lt(90)
    fd(70)
    lt(90)
    fd(100)
    lt(90)
    fd(70)


def rysuj_binarnie(p):
    liczba_bin = convert(p)
    up()
    rt(180)
    fd(300)
    rt(180)
    down()
    i = 0
    while(i < len(liczba_bin)):
        if(int(liczba_bin[i]) == 1):
            rysuj_kreske()
            skocz()
        if(int(liczba_bin[i]) == 0):
            rysuj_prostokacik()
            skocz()
        i += 1

rysuj_binarnie(154)
input()