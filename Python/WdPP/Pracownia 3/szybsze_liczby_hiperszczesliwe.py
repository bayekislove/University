def liczby_hiperszczesliwe(liczba_siodemek_z_rzedu, liczba_cyfr):
    n = liczba_siodemek_z_rzedu
    c = liczba_cyfr
    licznik = 0
    for i in range(int(''.join(["1", (c-n-1)*"0", n * "7"])), (10 ** c)):
        stringens = str(i)
        wycinek = stringens[0:(c-n+1)]
        a = "7"
        if a in wycinek:
            print(i)
            licznik += 1

liczby_hiperszczesliwe(7,10)