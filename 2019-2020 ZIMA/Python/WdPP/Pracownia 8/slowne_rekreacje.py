from random import choice
import time

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
        if pierwsze[el] != drugie_slownik[el]:
            return False
    return True

def ukladalne(st):
    kandydaci = set()
    wlasciwy_napis = (st.replace(" ", '')).lower()
    wlasciwy_slownik = slowo_slownik(wlasciwy_napis)
    for x in open('slowa.txt', encoding='utf-8'):
        if len(x[:-1]) > len(wlasciwy_napis):
            continue
        elif sprawdzacz(wlasciwy_slownik, x[:-1]) == True:
            kandydaci.add(x[:-1])
    return kandydaci

def sprawdzanie(st):
    start = time.time()
    scalone = st.replace(" ", '')
    zbior_kandydatow = ukladalne(st)
    literki_imie_nazwisko = slowo_slownik(scalone.lower())
    dobre = {}
    for el in zbior_kandydatow:
        for k in zbior_kandydatow:
            if len(k) + len(el) != len(scalone):
                continue
            else:
                temp = k + el
                if rownosc_wystapien(literki_imie_nazwisko, temp) == True:
                    if k not in dobre.keys() and el not in dobre.keys():
                        dobre[k] = el
                        dobre[el] = k
                        print(k + " " + el)
    stop = time.time()
    print(stop - start)

sprawdzanie("Kacper Bajkiewicz")
