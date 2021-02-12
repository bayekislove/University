from relacje_rownowaznosci import set_partition
from stopien_niepoporcjonalnosci import dhonndt

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

#komitety = {0 : "PiS", 1: "KO", 2:"SLD", 3:" PSL", 4:"Konfederacja", 5:"MN"}
komitety = {"PiS":1, "KO":2, "SLD":3, "PSL":4, "Konfederacja":5, "MN":6}

def mozliwe_koalicje(zbior):
    return set_partition(zbior)

def stworz_tablice(n):
    tab = []
    for okreg in range(41):
        pom_tab = []
        pom_tab.append(int(tabela[okreg][0]))
        tab.append(pom_tab)
    return tab

for wariant in mozliwe_koalicje(set(komitety.keys())):
    poparcia = stworz_tablice(len(wariant))
    nazwy = []
    for i in range(len(wariant)):
        skladowe = list(wariant[i])
        nazwy_w_koalicji = []
        for el in skladowe:
            nazwy_w_koalicji.append(el)
        for okreg in range(41):
            poparcie_w_okregu = 0
            for el in skladowe:
                if tabela[okreg][komitety[el]] != '–':
                    poparcie_w_okregu += float(tabela[okreg][komitety[el]])
            poparcia[okreg].append(poparcie_w_okregu)
        nazwy.append(nazwy_w_koalicji)
    wyniki = dhonndt(1, poparcia)
    for i in range(len(wyniki)):
        if wyniki[i] >= 307:
            print("Konstytucyjna: " + str(wyniki[i]) + " = " + ' + '.join(nazwy[i]))
        elif wyniki[i] > 230:
            if 'PiS' not in nazwy[i]:
                print("Bezwzględna: " + str(wyniki[i]) + " = " + ' + '.join(nazwy[i]))

