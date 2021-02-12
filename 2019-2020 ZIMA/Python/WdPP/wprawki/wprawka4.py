def macierz_ok(l):
    dlugosc = len(l)
    for i in range(dlugosc):
        if len(l[i]) != dlugosc:
            return False
    return True

def transpozycja_macierzy(macierz):
    if macierz_ok(macierz) == False:
        return "To nie jest poprawna macierz!"
    else:
        macierz_transponowana = []
        for i in range(len(macierz)):
            wiersz_macierzy = []
            for k in range(len(macierz)):
                wiersz_macierzy.append(macierz[k][i])
            macierz_transponowana.append(wiersz_macierzy)
        return macierz_transponowana

print(transpozycja_macierzy([[1, 1, 1], [2, 2, 2], [3, 3, 3]]))
print(transpozycja_macierzy([[4, 6, 7], [1]]))
print(transpozycja_macierzy([[5, 6, 7], [9, 0, 8], [4, 5, 6]]))
print(transpozycja_macierzy([[2, 3], [5, 6], [7, 8]]))