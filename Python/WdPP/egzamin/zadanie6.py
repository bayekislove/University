def srednia_liczba_cyfr(L):
    return (sum(map(lambda x: len(str(x)),L)))/len(L)

def czy_jest_tytulem(s): 
    return all(map(lambda x: x[0].upper() + x[1:].lower() == x, s.split()))

def maksymalny_skok(D): 
    return max(map(lambda x: abs(x-D[x]), D))

def posortowana_leksykograficznie(L): 
    return list(map(lambda y: int(y), sorted(list(map(lambda x: str(x), L)))))

print(srednia_liczba_cyfr([112,2,33]))
print(czy_jest_tytulem('tytul nei Tytuł'))
print(czy_jest_tytulem('Tytul To Tytuł'))
print(maksymalny_skok({1:2, 2:4, 3:6, 8:8}))
print(posortowana_leksykograficznie([1,4,55,222,9,10]))
