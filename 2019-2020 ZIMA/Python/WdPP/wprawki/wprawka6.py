def split(L):
    wynik = []
    srodek = (len(L) + 1) // 2
    pom = []
    for i in range(srodek):
        pom.append(L[i])
    wynik.append(pom)
    pom = []
    for i in range(srodek, len(L)):
        pom.append(L[i])
    wynik.append(pom)
    return(wynik)

def merge(lista1, lista2):
    wynik = []
    i = 0
    j = 0
    while((i+j) < len(lista1) + len(lista2)):
        if i >= len(lista1):
            for k in range(j, len(lista2)):
                wynik.append(lista2[k])
            return wynik
        elif j >= len(lista2):
            for k in range(i, len(lista1)):
                wynik.append(lista1[k])
            return wynik
        else:
            if lista1[i] < lista2[j]:
                wynik.append(lista1[i])
                i += 1
            else: 
                wynik.append(lista2[j])
                j += 1
    return wynik

def mergesort(L):
    k = split(L)
    if len(L) > 1:
        k[0] = mergesort(k[0])
        k[1] = mergesort(k[1])
        return merge(k[0], k[1])
    return L


print(mergesort([4, 1, 60, 3, 500, 70, 500]))