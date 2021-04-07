def liczba_pierwsza(p):
    x = 2
    while(x != p):
        if ((p % x) == 0):
            return True
        x += 1


def szczesliwe_liczby_pierwsze(x):
    p = 777
    licznik = 0
    while (p!=(x+1)):
        if ((("777") in str(p)) == True) and (liczba_pierwsza(p) != True ):
            print("Znaleziono szczęśliwą liczbę pierwszą: " + str(p))
            licznik += 1
        p = p + 1
    print("Liczba szczęśliwych liczb pierwszych: " + str(licznik))
    

szczesliwe_liczby_pierwsze(100000)
print("KONIEC")




        