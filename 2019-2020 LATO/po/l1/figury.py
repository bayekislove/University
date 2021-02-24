from math import pi

def nowy_kwadrat(x1, y1, bok): #x2 < x1, x1 ogranicza figurę od prawej strony
    if bok <= 0:
        return ValueError 
    return [0, x1, y1, bok]

def nowe_kolo(sx, sy, r):
    if r < 0:
        return ValueError
    return [1, sx, sy, r]

def nowy_trojkat(x1, x2, y3, yx1):
    return [2, x1, x2, y3, yx1]

def przesun(figura, wektor_x, wektor_y):
    if figura[0] == 0:
        figura[1] += wektor_x
        figura[2] += wektor_y
    if figura[0] == 1:
        figura[1] += wektor_x
        figura[2] += wektor_y
    if figura[0] == 2:
        figura[1] += wektor_x
        figura[2] += wektor_x
        figura[3] += wektor_y
    return figura

def pole(figura):
        if figura[0] == 0:
            return (figura[3]) ** 2
        if figura[0] == 1:
            return (pi * (figura[2] ** 2))
        if figura[0] == 2:
            return (abs(figura[1] - figura[2]) * (abs(figura[3] - figura[4])) / 2)

def sumapol(tab):
    suma = 0
    for i in range(len(tab)):
        suma += pole(tab[i])
    return suma

kolo = nowe_kolo(0, 0, 3)
print(kolo)
print(przesun(kolo, 2, 3))
print(pole(kolo))
kwadrat = nowy_kwadrat(2, 4, 5)
print(przesun(kwadrat, 2, 3))
print(pole(kwadrat))
trojkat = nowy_trojkat(0, 2, 2, 0)
print(pole(trojkat))
print(przesun(trojkat, 1, 0))
print(sumapol([trojkat,kolo,kwadrat]))
