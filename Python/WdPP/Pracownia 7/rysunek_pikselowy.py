from turtle import *
speed('fastest')
k = open('obrazek.txt', encoding='utf-8')
licznik = 0
rysunek_po_pikselach = []
for wiersz in k:
    rysunek_po_pikselach.append(wiersz.split())

def kwadracik(bok):
    for i in range(4):
        fd(bok)
        lt(90)
    fd(bok)
def wracaj(k, bok):
    up()
    rt(180)
    fd(k)
    rt(90)
    fd(bok)
    rt(90)
    down()
def daj_kolorek(lista):
    temp_lista = lista.strip(")")                           ### chcemy obedrzeć nasz rgb z nawiasów i zamienić to 
    wlasciwa_lista = (temp_lista.strip("(")).split(',')     ### na listę kolejno elementu r, g i b
    return wlasciwa_lista

# tutaj zaczyna się właściwy rysunek #
up()
down()
for i in range(len(rysunek_po_pikselach)):
    for k in range(len(rysunek_po_pikselach[i])):
        kolorek = daj_kolorek(rysunek_po_pikselach[i][k])
        fillcolor(float(kolorek[0]) / 255, float(kolorek[1]) / 255, float(kolorek[2]) / 255)
        pencolor(float(kolorek[0]) / 255, float(kolorek[1]) / 255, float(kolorek[2]) / 255)
        begin_fill()
        kwadracik(5)
        end_fill()
    wracaj(5 * len(rysunek_po_pikselach[i]), 5)

input()



