def liczby_pierwsze(a, b):
    liczby = []
    for i in range(2, b+1):
        liczby.append(i)
    indeks = 0
    while(indeks < len(liczby)):
        kasowanie = indeks
        if liczby[indeks] != 0:
            while((kasowanie + liczby[indeks]) < (len(liczby)-1)):
                kasowanie += liczby[indeks]
                liczby[kasowanie] = 0
        indeks += 1
    pierwsze = []
    for i in liczby:
        if i >= a:
            pierwsze.append(i)
    return pierwsze

def palindromiczne_liczby_pierwsze(a, b):
    pierwsze = liczby_pierwsze(a, b)
    palindromy = []
    for e in pierwsze:
        wyraz = str(e)
        if (len(wyraz) == 1):
            palindromy.append(e)
        else:
            i = 0
            while(i < ((len(wyraz)/2)+1)):
                if (wyraz[i] != wyraz[-i-1]):
                    break
                elif (wyraz[i] == wyraz[-i-1]):
                    if(i >= (len(wyraz)/2)):
                        palindromy.append(int(wyraz))
                        break
                i += 1
    print(palindromy)

palindromiczne_liczby_pierwsze(2,1000)



            