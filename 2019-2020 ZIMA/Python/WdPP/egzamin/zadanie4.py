def wczytaj(plik):
    slownik = {}
    for line in open(plik):
        line = line.split()
        if line[0] not in slownik.keys():
            slownik[line[0]] = []
        for i in range(1,len(line)):
            slownik[line[0]].append(float(line[i]))
    return slownik

def wypisz_raport(slownik):
    raport = []
    for imie in slownik.keys():
        raport.append([sum(slownik[imie]),imie])
    raport.sort(reverse = True)
    for element in raport:
        print(element[1].capitalize() + ' łącznie zebrał/a grzyby o masie ' + str(element[0]) + ' kg') 

def oszust(slownik):
    oszust = ['',0]
    for imie_oszusta in slownik.keys():
        dowod = len(slownik[imie_oszusta]) - len(set(slownik[imie_oszusta]))
        if oszust[1] < dowod:
            oszust[0] = imie_oszusta
            oszust[1] = dowod
    if oszust[1] != 0:
        print("Największym oszustem jest " + str(oszust[0]).capitalize())
    else:
        print("Żaden wynik się nie powtórzył")



slownik = wczytaj('plik.txt')
print(wczytaj('plik.txt'))
wypisz_raport(slownik)
oszust(slownik)
