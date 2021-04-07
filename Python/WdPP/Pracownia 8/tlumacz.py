from random import choice

pol_ang = {}
for wiersz in open('pol_ang.txt',encoding='utf-8'):
    wiersz = wiersz.strip()
    if '=' not in wiersz:
        continue
    pola = wiersz.split('=')
    if len(pola) != 2:
        continue
    p, a = pola
    if p in pol_ang:
        pol_ang[p].append(a)
    else:
        pol_ang[p] = [a] 

def popularnosc():
    popularnosc_slowa = {}
    for linia in open('korpus.txt', encoding='utf-8'):
        elementy_linii = linia.split()
        for k in elementy_linii:
            if k in popularnosc_slowa.keys():
                popularnosc_slowa[k] += 1
            else:
                popularnosc_slowa[k] = 1
    return popularnosc_slowa

popularnosc_slowa = popularnosc()

def popularnosc_slowka(k):
    if k in popularnosc_slowa.keys():
        return popularnosc_slowa[k]
    else:
        return 0 

def najbardziej_popularne(lista_tlumaczen):
    if len(lista_tlumaczen) == 1:
        return lista_tlumaczen[0]
    else:
        maks = 0
        takie_same = []
        for el in lista_tlumaczen:
            if int(popularnosc_slowka(el)) > maks:
                maks = popularnosc_slowka(el)
                takie_same.clear()
                takie_same.append(el)
            elif int(popularnosc_slowka(el)) == maks:
                takie_same.append(el)
        return choice(takie_same)

def tlumacz(zdanie):
    wyrazy = zdanie.split()
    wynik = []
    for w in wyrazy:
        if w in pol_ang:
            wynik.append(najbardziej_popularne(pol_ang[w]))
        else:
            wynik.append('[?]')
    return ' '.join(wynik)

for i in range(7):
    print(tlumacz('to jest kotek'))
    print(tlumacz('lubić chodzić do kino'))