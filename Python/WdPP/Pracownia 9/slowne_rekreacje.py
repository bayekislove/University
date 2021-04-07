from random import choice
import time
from itertools import permutations

def slowo_slownik(k):
    literki = {}
    for i in range(len(k)):
        if k[i] in literki.keys():
            literki[k[i]] += 1
        else:
            literki[k[i]] = 1
    return literki

def sprawdzacz(pier, dr): #z pierwszego ukladamy drugie
    drugie = slowo_slownik(dr)
    for el in drugie.keys():
        if el not in pier.keys():
            return False
        elif pier[el] < drugie[el]:
            return False
    return True

def rownosc_wystapien(pierwsze, drugie): #pierwsze to imie i naziwksko
    drugie_slownik = slowo_slownik(drugie)
    for el in pierwsze.keys():
        for k in drugie_slownik.keys():
            if k not in pierwsze.keys():
                return False
            if el not in drugie_slownik.keys():
                return False
        if pierwsze[el] >= drugie_slownik[el]:
            return False
    return True

def ukladalne(st):   #zmodyfikowano
    kandydaci = set()
    wlasciwy_napis = (st.replace(" ", '')).lower()
    wlasciwy_slownik = slowo_slownik(wlasciwy_napis)
    for x in open('slowa.txt', encoding='utf-8'):
        if len(x[:-1]) >= len(wlasciwy_napis) - 1:
            continue
        elif sprawdzacz(wlasciwy_slownik, x[:-1]) == True:
            kandydaci.add(x[:-1])
    return kandydaci

def zrob_trzecie_slowa(scalone, imieinaziwsko):
    trzecie_slownik = {}
    slownik_scalone = slowo_slownik(scalone)
    for el in imieinaziwsko.keys():
        for k in slownik_scalone.keys():
            if k not in imieinaziwsko.keys():
                continue
            if el not in imieinaziwsko.keys():
                continue
        if imieinaziwsko[el] < slownik_scalone[el]:
            continue
        if imieinaziwsko[el] > slownik_scalone[el]:
            if el in trzecie_slownik.keys():
                trzecie_slownik[el] += 1
            else:
                trzecie_slownik[el] = 1
    literki_trzecie = []
    for literka in trzecie_slownik.keys():
        for k in range(trzecie_slownik[literka]):
            literki_trzecie.append(literka)
    kandydaci = list(permutations(literki_trzecie))
    for element in kandydaci:
        if element not in zbior_kandydatow:
            kandydaci.remove(element)
    return kandydaci

def sprawdzanie(st):
    scalone = st.replace(" ", '')
    zbior_kandydatow = ukladalne(st)
    print(len(zbior_kandydatow))
    literki_imie_nazwisko = slowo_slownik(scalone.lower())
    dobre = {}
    for el in zbior_kandydatow:
        for k in zbior_kandydatow:
            if len(k) + len(el) != len(scalone):
                continue
            else:
                temp = k + el
                trzecie_slowka = zrob_trzecie_slowa(temp, literki_imie_nazwisko)
                if rownosc_wystapien(literki_imie_nazwisko, temp) == True:
                    for element in trzecie_slowka:
                        if k not in dobre.keys() and el not in dobre.keys():
                            dobre[k] = el
                            dobre[el] = k
                            print(k + " " + el + " " + element)

zbior_kandydatow = ukladalne("Bolesław Prus")
sprawdzanie("Bolesław Prus")


#zmiany:
#sprawdzac liczby co najmniej o 2 mniejsze rowne od wyjsciowej done
#dopisac funkcje tworzaca trzecie slowo, ktora bierze zamienione na slownik dwa slowa i patrzy czy wszystkie wystapienia tam sa mniejsze rowne
#   jesli tak, to zapisuje dopelnienie tych slow w slowniku wraz z liczba jej wystapien
#   tworzy liste z dopelnieneim imienia i nazwiska(uwzgledniajac liczbe wystapien)
#   jako kolejna liste zapisuje permutacje listy z dopelnieniami 
#   sprawdza czy kazdy z tych elementow listy permutacji znjaduje sie w liscie kandydatow
#   jesli tak, to drukuje te trzy slowa
#   jesli nie, to leci do przodu 