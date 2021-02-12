def liczby_pierwsze(a, b):
    liczby = []
    for i in range(2, b+1):
        liczby.append(i)
    indeks = 0
    while(indeks < len(liczby)):
        kasowanie = indeks
        if liczby[indeks] != 0:
            while((kasowanie + liczby[indeks]) <= (len(liczby)-1)):
                kasowanie += liczby[indeks]
                liczby[kasowanie] = 0
        indeks += 1
    pierwsze = []
    for i in liczby:
        if i >= a:
            pierwsze.append(i)
    return pierwsze


def pierwsze_dzielniki(n):
    dzielniki = set()
    pierwsze_z_przedzialu = liczby_pierwsze(2, n)
    i = 0
    while(i < len(pierwsze_z_przedzialu)):
        if n % pierwsze_z_przedzialu[i] == 0:
            dzielniki.add(str(pierwsze_z_przedzialu[i]))
        i += 1
    return dzielniki

print(pierwsze_dzielniki(793))
print(pierwsze_dzielniki(31))
print(pierwsze_dzielniki(8))
print(pierwsze_dzielniki(999))
