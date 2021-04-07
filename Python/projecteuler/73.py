def counting_fractions(d): #oznaczenia w treści zadania 
    def gcd(a, b): #szukacz greatest common divisor 
        while(b != 0):
            t = a
            a = b
            b = t % b
        return a
    licznik = 0
    for n in range(1, d + 1):
        for kandydat in range(int(n/3) + 1, int((n-1)/2) + 1):
            if gcd(kandydat, n) == 1:
                licznik += 1
    return licznik

print(counting_fractions(12000))


