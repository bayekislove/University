from turtle import *
from random import randint, random
tracer(0,1)
k = open('obrazek.txt', encoding='utf-8')
rysunek_po_pikselach = []
wszystkie_piksele = []
for wiersz in k:
    rysunek_po_pikselach.append(wiersz.split())
for i in range(len(rysunek_po_pikselach)):
    for k in range(len(rysunek_po_pikselach[i])):
        wszystkie_piksele.append(rysunek_po_pikselach[i][k])
ile_pikseli = len(wszystkie_piksele)

def kwadracik(bok):
    for i in range(4):
        fd(bok)
        lt(90)
def daj_kolorek(lista):
    temp_lista = lista.strip(")")                           ### chcemy obedrzeć nasz rgb z nawiasów i zamienić to 
    wlasciwa_lista = (temp_lista.strip("(")).split(',')     ### na listę kolejno elementu r, g i b
    return wlasciwa_lista

# tutaj zaczyna się właściwy rysunek #
for s in range(ile_pikseli):
    i = randint(0, len(rysunek_po_pikselach)-1)
    k = randint(0, len(rysunek_po_pikselach[i])-1)
    kolorek = daj_kolorek(rysunek_po_pikselach[i][k])
    up()
    goto(i * 5, k * 5)
    down()
    fillcolor(float(kolorek[0]) / 255, float(kolorek[1]) / 255, float(kolorek[2]) / 255)
    pencolor(float(kolorek[0]) / 255, float(kolorek[1]) / 255, float(kolorek[2]) / 255)
    begin_fill()
    kwadracik(5)
    end_fill()
    up()
    goto(0,0)
    down()
    rysunek_po_pikselach[i].remove(rysunek_po_pikselach[i][k])
    if len(rysunek_po_pikselach[i]) == 0:
        rysunek_po_pikselach.remove(rysunek_po_pikselach[i])

input()



