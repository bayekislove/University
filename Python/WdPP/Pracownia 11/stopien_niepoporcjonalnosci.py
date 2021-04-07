tabela = []
i = 0
for line in open('wyniki_wyborow.tsv', encoding='utf-8'):
    if i == 0:
        i += 1
        pass
    else:
        s = line.replace('\n', '')
        pom_tab = (s.replace(',', '.')).split("\t")
        tabela.append(pom_tab[2:9])

doskonala_proporcjonalnosc = [43.59 * 4.6, 27.40 * 4.6, 12.56* 4.6, 8.55* 4.6, 6.81* 4.6, 0.17* 4.6]

def dhonndt(t, wyniki):
    mandaty = [0, 0, 0, 0, 0, 0]
    for okreg in range(41):
        wszystkie_ilorazy = [] #tutaj skladujemy wszystkie ilorazy (bedzie to lista list)
        for i in range(1,len(wyniki[okreg])): #dla kazdego komitetu wyznaczamy ilorazy
            for k in range(1, int(wyniki[okreg][0]) + 1): ##tutaj wyznaczamy tyle ilorazow, ile mandatow jest do zdobycia
                if wyniki[okreg][i] == '–':
                    continue
                ilor_kom = []
                iloraz_pom = float(wyniki[okreg][i]) / (k ** t) #wyznaczamy odpowiedni k-ty iloraz
                ilor_kom.append(iloraz_pom)
                ilor_kom.append(i)
                wszystkie_ilorazy.append(ilor_kom) #do wszystkich ilorazow wrzucamy wynik ([0]) i nazwe komitetu ([1])
        wszystkie_ilorazy.sort(reverse = True)
        for k in range(int(tabela[okreg][0])):
            mandaty[wszystkie_ilorazy[k][1] - 1] += 1
    return mandaty

def stopien_propocjonalnosci(k):
    niedokladnosc_proporcjonalnosci = 0
    dhonndtem = dhonndt(k, tabela)
    for i in range(6):
        dhonndtem[i] -= doskonala_proporcjonalnosc[i]
        niedokladnosc_proporcjonalnosci += dhonndtem[i]
x = []
y = []

for k in range(1, 200):
    waga = k / 100
    x.append(stopien_propocjonalnosci(waga))
    y.append(waga)
