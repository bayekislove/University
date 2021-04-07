def numsum(num): #to jest typowa funckcja zliczająca sumę cyfr liczby, bierzemy ostatnia cyfre z prawej a pozniej skracamy
    suma = 0 #cala liczbe o te cyfre
    for _ in range(len(str(num))):
        suma += num % 10
        num = num // 10
    return suma

def iteration(a,b):
    max = 0
    for i in range(a , 0, -1): #idziemy od konca, bo tu jest najwieksze prawdopodobienstwo, ze znajdziemy liczbe
        for k in range(b, 0, -1): #ktora nas interesuje (bo bedzie wieksza liczba, czyli wieksza suma jej cyfr)
            temp = i ** k           #ad l10 l11 iterujemy sobie po kolejnych liczbach
            if len(str(temp))*9 < max: #jesli dlugosc liczby * 9 bedzie mniejsza od naszej obecnej wartosci maksymalnej, to go do
                continue        #kolejnej iteracji (bo dlugosc liczby * 9 to najwieksza suma cyfr, jaka mozemy sprawdzac, skoro nie 
            if numsum(temp) > max:#przeszkoczymy obecnego maxa to nie ma co tracic czasu na potegowanie obecnej komibnacji i,k
                max = numsum(temp) #jesli suma cyfr wieksza nizeli max, to nowym maxem jest ta suma cyfr
    return max #zwracamy maxa
print(iteration(100,100))

