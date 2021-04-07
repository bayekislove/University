def stworz_slownik():
    wartosci = {}
    for i in range(1,21):
        for k in range(1, 4):
            if i * k in wartosci.keys():
                wartosci[i * k] += 1
            else:
                wartosci[i * k] = 1
    wartosci[25] = 50
    return wartosci

def sposoby_na_jednego(val):
    wartosci = stworz_slownik()
    ile = 0
    for i in range(1, 21):
        if 2*i < val:
            pom = val - 2*i
            used = []
            for kandydat in wartosci.keys():
                if kandydat == pom:
                    ile += wartosci[kandydat]
                    print(str(2*i) + " " + str(wartosci[kandydat]) + "\n")
                elif kandydat < pom:
                    if pom - kandydat in wartosci.keys():
                        if kandydat not in used:
                            ile += wartosci[kandydat] * wartosci[pom-kandydat]
                            print(str(2*i) + " " + str(wartosci[kandydat]) + " " + str(wartosci[pom-kandydat]) + "\n")
                            used.append(pom-kandydat)
        if 2*i == val:
            print("A")
            ile += 1
    if val - 50 < 0:
        pom = val - 50
        used = []
        for kandydat in wartosci.keys():
            if kandydat == pom:
                ile += wartosci[kandydat]
                continue
            elif kandydat < pom:
                if pom - kandydat in wartosci.keys():
                    if kandydat not in used:
                        ile += wartosci[kandydat] * wartosci[pom-kandydat]
                        used.append(pom-kandydat)
    return ile 

def znajdz(ran):
    ile = 0
    for i in range(1, ran+1):
        ile += sposoby_na_jednego(i)
    return ile

print(sposoby_na_jednego(6))
#print(znajdz(100))