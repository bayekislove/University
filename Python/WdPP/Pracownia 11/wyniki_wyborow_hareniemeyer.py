tabela = []
for line in open('wyniki_wyborow.tsv', encoding='utf-8'):
    s = line.replace('\n', '')
    pom_tab = (s.replace(',', '.')).split("\t")
    tabela.append(pom_tab[2:9])

mandaty = [0, 0, 0, 0, 0, 0, 0]



for okreg in range(1, 42):
    wszystkie_ilorazy = [] #tutaj skladujemy wszystkie ilorazy (bedzie to lista list)
    przyznane_okreg = 0
    for i in range(1,7): #dla kazdego komitetu wyznaczamy ilorazy
        if tabela[okreg][i] == '–':
            continue
        ilor_kom = []
        iloraz_pom = float(tabela[okreg][i]) * int(tabela[okreg][0]) / 100  #wyznaczamy odpowiedni k-ty iloraz
        przyznane_okreg += int(iloraz_pom)
        ilor_kom.append(iloraz_pom)
        ilor_kom.append(i)
        wszystkie_ilorazy.append(ilor_kom) #do wszystkich ilorazow wrzucamy wynik ([0]) i nazwe komitetu ([1])
        mandaty[i-1] += int(iloraz_pom)
    if int(tabela[okreg][0]) < int(przyznane_okreg):
        wszystkie_ilorazy.sort(reverse = True)
    for s in range(int(tabela[okreg][0]) - int(przyznane_okreg)):
        mandaty[wszystkie_ilorazy[s][1]] += 1
    
for i in range(6):
    print('Komitet nr ' + str(i+1) + ' zdobył: ' + str(mandaty[i]) + ' mandaty/ów')
