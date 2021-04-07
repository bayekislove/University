from math import sqrt

def blok(n, znak):
    return n * znak

def bloki(m):
    lista_napisow = []
    for i in range(1, m+1):
        if i % 6 == 1:
            lista_napisow.append(list(blok(i, '@')))
        if i % 6 == 2:
            lista_napisow.append(list(blok(i, '*')))
        if i % 6 == 3:
            lista_napisow.append(list(blok(i, '#')))
        if i % 6 == 4:
            lista_napisow.append(list(blok(i, '&')))
        if i % 6 == 5:
            lista_napisow.append(list(blok(i, '%')))
        if i % 6 == 0:
            lista_napisow.append(list(blok(i, '$')))
    return lista_napisow

def filtr(lista):
    koncowa_lista = []
    k = 0
    while(k < len(lista)):
        a = int(sqrt(len(lista[k])))
        b = float(sqrt(len(lista[k])))
        if a == b:
            koncowa_lista.append((''.join(lista[k])))
        k += 1
    return koncowa_lista

k = 0
while(k < len(filtr(bloki(111)))):
    print(filtr(bloki(111))[k])
    k += 1