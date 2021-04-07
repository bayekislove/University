def energia_collatza(n):
    energia = 0
    while(n != 1):
        if(n % 2 == 0):
            n = n / 2
        else:
            n = 3 * n + 1
        energia = energia + 1
    return energia

def mediana(lista):
    if len(lista) % 2 != 0:
        indeks = ((len(lista)+1) / 2) - 1
        mediana = lista[indeks]
    elif len(lista) % 2 == 0:
        indeks1 = int((len(lista)/2) - 1)
        indeks2 = int((len(lista)/2)) 
        mediana = (lista[indeks1] + lista[indeks2]) / 2
    return mediana

def analiza_collatza(a,b):
    energie_coll = []
    for i in range(a,b+1):
        energia_collatza(i)
        energie_coll.append(energia_collatza(i))
    suma = 0
    for el in energie_coll:
        suma += int(el)
    eśr = suma / len(energie_coll)
    print("Średnia energia collatza liczb z przedziału <" + str(a) + "," + str(b) + "> to " + str(eśr))
    print("Maksymalna energia collatza wśród tych liczb to:" + str(max(energie_coll)))
    print("Minimalna energia collatza wśród tych liczb to:" + str(min(energie_coll)))
    print("Mediana energii collatza liczb z tego przedziału to: " + str(mediana(sorted(energie_coll)))) 

analiza_collatza(1,50)

