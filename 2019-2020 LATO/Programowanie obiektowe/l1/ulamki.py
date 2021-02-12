def nowy_ulamek(licznik, mianownik):
    if mianownik == 0:
        return ZeroDivisionError
    def gcd(a, b):
        while(b != 0):
            t = a
            a = b
            b = t % b
        return a
    gcdd = gcd(licznik, mianownik)
    return [int(licznik / gcdd), int(mianownik / gcdd)]

def dodaj_ulamki(u1, u2):
    def gcd(a, b):
        while(b != 0):
            t = a
            a = b
            b = t % b
        return a
    nowy_mianownik = u1[1] * u2[1]
    nowy_licznik = u1[0] * (nowy_mianownik / u1[1]) + u2[0] * (nowy_mianownik / u2[1])
    gcdd = gcd(nowy_licznik, nowy_mianownik)
    return [int(nowy_licznik / gcdd), int(nowy_mianownik / gcdd)]

def odejmij_ulamki(u1, u2):
    def gcd(a, b):
        while(b != 0):
            t = a
            a = b
            b = t % b
        return a
    nowy_mianownik = u1[1] * u2[1]
    nowy_licznik = u1[0] * (nowy_mianownik / u1[1]) - u2[0] * (nowy_mianownik / u2[1])
    gcdd = gcd(nowy_licznik, nowy_mianownik)
    return [int(nowy_licznik / gcdd), int(nowy_mianownik / gcdd)]

def przemnoz_ulamki(u1, u2):
    def gcd(a, b):
        while(b != 0):
            t = a
            a = b
            b = t % b
        return a
    nowy_mianownik = u1[1] * u2[1]
    nowy_licznik = u1[0] * u2[0]
    gcdd = gcd(nowy_licznik, nowy_mianownik)
    return [int(nowy_licznik / gcdd), int(nowy_mianownik / gcdd)]

def podziel_ulamki(u1, u2):
    def gcd(a, b):
        while(b != 0):
            t = a
            a = b
            b = t % b
        return a
    nowy_licznik = u1[0] * u2[1]
    nowy_mianownik = u1[1] * u2[0]
    gcdd = gcd(nowy_licznik, nowy_mianownik)
    return [int(nowy_licznik / gcdd), int(nowy_mianownik / gcdd)]