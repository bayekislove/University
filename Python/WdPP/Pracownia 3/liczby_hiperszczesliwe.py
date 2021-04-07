def liczba_hiperszczesliwa(liczba_siodemek_z_rzedu, liczba_cyfr):
    n = liczba_siodemek_z_rzedu
    c = liczba_cyfr
    licznik = 0
    for i in range(int(''.join(["1", (c-n-1)*"0", n * "7"])), ((10 ** c) - 1)):       #zakres w liczbach c cyfrowych
        a = 1
        liczba = c * ["0"]
        wystapienia = 0
        while((a <= c) and (wystapienia <= 7)):                                   #tutaj do tablicy chcemy dostać kolejne cyfry tej liczby
            print(i)
            liczba[c-a] = int(i % 10)
            if liczba[c-a] == 7:
                wystapienia += 1
            if (liczba[c-a] == 7) and (liczba[c-a-1] != 7):
                break
            if ((a > (c-10)) and (wystapienia == 0)):
                break
            a += 1
            i = (i-int(liczba[c-a])) / 10
                        
    print("Liczba liczb hiperszczęśliwych: " + licznik)



liczba_hiperszczesliwa(7,10)



        
        

