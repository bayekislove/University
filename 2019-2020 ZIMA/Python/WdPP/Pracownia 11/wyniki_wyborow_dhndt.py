tabela = []
for line in open('wyniki_wyborow.tsv', encoding='utf-8'):
    s = line.replace('\n', '')
    pom_tab = (s.replace(',', '.')).split("\t")
    tabela.append(pom_tab[2:9])

mandaty = [0, 0, 0, 0, 0, 0, 0]

for okreg in range(1, 42):
    wszystkie_ilorazy = [] #tutaj skladujemy wszystkie ilorazy (bedzie to lista list)
    for i in range(1,7): #dla kazdego komitetu wyznaczamy ilorazy
        for k in range(1, int(tabela[okreg][0]) + 1): ##tutaj wyznaczamy tyle ilorazow, ile mandatow jest do zdobycia
            if tabela[okreg][i] == '–':
                continue
            ilor_kom = []
            iloraz_pom = float(tabela[okreg][i]) / k #wyznaczamy odpowiedni k-ty iloraz
            ilor_kom.append(iloraz_pom)
            ilor_kom.append(i)
            wszystkie_ilorazy.append(ilor_kom) #do wszystkich ilorazow wrzucamy wynik ([0]) i nazwe komitetu ([1])
    wszystkie_ilorazy.sort(reverse = True)
    for k in range(int(tabela[okreg][0])):
        mandaty[wszystkie_ilorazy[k][1] - 1] += 1
    mandaty
for i in range(6):
    print('Komitet nr ' + str(i+1) + ' zdobył: ' + str(mandaty[i]) + ' mandaty/ów')
