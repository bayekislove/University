#użyję lematu, że przez wzgląd na to, że a b c są względnie pierwsze, to rad(abc) = rad(a) * rad(b) * rad(c)
#to oszczedza nam w chuj pamieci
#prosty i mechaniczny dowod pozostawiam uwaznemu sluchaczowi

from math import sqrt

def primes(x, y):
    def gcd(a, b):
        while(b != 0):
            t = a
            a = b
            b = t % b
        return a
    if gcd(x, y) == 1:
        return True
    return False

def sito(zakres):
    tablica_pierwszych = [1] * (zakres + 1)
    for i in range(2, zakres+1):
        if tablica_pierwszych[i] == 1:
            k = i
            while (k + i) <= zakres:
                k += i
                tablica_pierwszych[k] = 0
    return tablica_pierwszych

def rad(num, tablica_pierwszych):
    radd = 1 #tu bedzeimy przechowywac wynik funkcji rad
    for i in range(2, int(sqrt(num)) + 1):
        if (tablica_pierwszych[i] == 1) and (num % i == 0):
            radd = radd * i
            while(num % i == 0):
                num = int(num / i)
    return radd * num

def szukanie_sumy(zakres):
    suma = 0
    licznik = 0
    t = sito(zakres+1) #nazwę to "t", tutaj przechowujemy tablicę powstałą z sita erastotenesa (nazwa krotka zeby linijka 42 sie nie rozjebala)
    for i in range(1, zakres):
        if i % 1000 == 0:
            print(i)
        for k in range(1, i):
            if (i+k) > zakres:
                continue
            if primes(i, k) == True:
                if rad(i, t) * rad(k, t) * rad(i+k, t) < (i+k):
                    licznik += 1
                    suma += i + k
    return suma, licznik

print(szukanie_sumy(5000))