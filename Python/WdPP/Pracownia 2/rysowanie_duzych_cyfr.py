from duze_cyfry import daj_cyfre

def rysuj_cyfre(k):
    liczba = str(k)
    do_wydrukowania = []
    for cos in range(6):
        do_wydrukowania.append('')
    for i in range(len(liczba)):
        for b in range(5):
            do_wydrukowania[b] += (daj_cyfre(int(liczba[i])))[b] + "     "
    for i in range(6):
        print(do_wydrukowania[i])

rysuj_cyfre(35454)
rysuj_cyfre(123)
rysuj_cyfre(12345)

