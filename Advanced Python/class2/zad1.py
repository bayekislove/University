from typing import Dict, List
from copy import deepcopy

ile_mandatow_w_jakim_okregu = [12,8,14,12,13,15,12,12,10,9,12,8,14,10,9,10,9,12,20,12,12,11,15,14,12,14,9,7,9,9,12,9,16,8,10,12,9,9,10,8,12]

class Komitet:
    
    def __init__(self, nazwa) -> None:
        self.kandydaci = []
        self.liczba_glosow_na_komitet = 0
        self.nazwa = nazwa

    def wybrani_z_komitetu(self, liczba_mandatow):
        self.kandydaci = sorted(self.kandydaci, reverse=True, key=lambda x : x[1])
        return [self.kandydaci[i][0] for i in range(liczba_mandatow)]

    def dodaj_kandydata(self, kandydat, l_glosow):
        self.kandydaci.append((kandydat, l_glosow))
        self.liczba_glosow_na_komitet += l_glosow

def wynik_wyborow(komitety : List[Komitet], mandaty):
    ilorazy = []
    for komitet in komitety:
        for i in range(1, mandaty + 1):
            ilorazy.append((komitet.nazwa, komitet.liczba_glosow_na_komitet / i))
    ilorazy = sorted(ilorazy, reverse=True, key=lambda x: x[1])
    przyznane_mandaty = { komitet.nazwa : 0 for komitet in komitety }

    for i in range(mandaty):
        przyznane_mandaty[ilorazy[i][0]] += 1

    wybrani = []
    for komitet in komitety:
        wybrani.append((komitet.wybrani_z_komitetu(przyznane_mandaty[komitet.nazwa]), komitet.nazwa))
    return wybrani

def dane_o_wyborach(plik):
    spreparowane_dane = [] #[ (nr_okregu, Imię i nazwisko, komitet, liczba_głosów) ]
    for line in open(plik, 'r', encoding='utf-8'):
        line = line.strip('\n').split(';')
        spreparowane_dane.append((int(line[0][1:-1]), line[3][1:-1], f"{line[7][1:-1]} {line[6][1:-1]}", int(line[13][1:-1])))
    #uzupełnianie słownika
    glosy_na_komitety = {}
    for osoba in spreparowane_dane:
        glosy_na_komitety[osoba[1]] = 0
    for osoba in spreparowane_dane:
        glosy_na_komitety[osoba[1]] += osoba[3]
    calkowita_liczba_glosow = sum(glosy_na_komitety.values())
    prog_wyborczy = calkowita_liczba_glosow * 0.05
    pom_glosy_na_komitety = deepcopy(glosy_na_komitety)
    for komitet in pom_glosy_na_komitety.keys():
        if glosy_na_komitety[komitet] < prog_wyborczy:
            del glosy_na_komitety[komitet]
    spreparowane_dane = [ x for x in spreparowane_dane if (x[1] in glosy_na_komitety.keys()) ]
    
    kandydaci_po_okregach = { x : [] for x in range(1, 42) }
    for osoba in spreparowane_dane:
        kandydaci_po_okregach[osoba[0]].append(osoba[1:])
    
    uzyskali_mandat = []
    for (i, kandydaci) in kandydaci_po_okregach.items():
        glosy_na_komitety = { x : Komitet(x) for x in glosy_na_komitety.keys() }
        for osoba in kandydaci:
            glosy_na_komitety[osoba[0]].dodaj_kandydata(osoba[1], osoba[2])
        for wybrani, komitet in wynik_wyborow(glosy_na_komitety.values(), ile_mandatow_w_jakim_okregu[i-1]):
            for wybrany in wybrani:
                uzyskali_mandat.append( (wybrany, komitet) )
    
    print("W wyborach mandat uzyskali:")
    mandaty_komitetow = { x : 0 for x in glosy_na_komitety.keys() }
    for wybrany in uzyskali_mandat:
        mandaty_komitetow[wybrany[1]] += 1
        print(wybrany[0])
    print("Mandaty z podziałem na komitety: ")
    for komitet, mandaty in sorted(mandaty_komitetow.items(), key=lambda x:x[1], reverse=True):
        print(f"{komitet} : {mandaty}")



if __name__ == '__main__':
    dane_o_wyborach('kandydaci_sejm_2011.csv')

    ### WYNIKI WYBORÓW SĄ TAKIE SAME, PO DOSTAŁO JEDEN MANDAT WIĘCEJ ZA MNIEJSZOŚĆ NIEMIECKĄ BO WEDŁUG 
    ### TREŚCI ZADANIA NIE UWZGLĘDNIAMY ZWOLNIENIA Z PROGU WYBORCZEGO DLA KOMITETÓW MNIEJSZOŚCI NARODOWEJ