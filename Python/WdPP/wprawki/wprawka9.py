def pogrupowane(L):
    uzyte = set()
    kolejnosc = []
    for i in range(len(L)):
        if L[i] in uzyte:
            continue
        else:
            uzyte.add(L[i])
            element = L[i]
            wystapienia = 0
            for k in range(len(L)):
                if L[k] == L[i]:
                    wystapienia += 1
            kolejnosc.append([element, wystapienia])
    kolejnosc = sorted(kolejnosc)
    koniec = []
    for i in range(len(kolejnosc)):
        pom = []
        for _ in range(kolejnosc[i][1]):
            pom.append(kolejnosc[i][0])
        koniec.append(pom)
    return(koniec)

print(pogrupowane([1,2,3,4,4,5,1,7]))

        


                        
