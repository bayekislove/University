k = open('lala.txt', encoding='utf-8')
wszystkie_slowa = {}
licznik = {}
for linia in open('lala.txt', encoding='utf-8'):
    for el in linia.split():
        napisik = (str(el)).lower()
        if napisik == "—" :
            continue
        if "." in napisik:
            napisik = napisik.replace('.', '')
        if "…" in napisik:
            napisik = napisik.replace('…', '')
        if "," in napisik:
            napisik = napisik.replace(',', '')
        if "?" in napisik:
            napisik = napisik.replace("?", '')
        if "!" in napisik:
            napisik = napisik.replace("!", '')
        if ":" in napisik:
            napisik = napisik.replace(":", '')
        if '*' in napisik:
            napisik = napisik.replace("*", '')
        if ')' in napisik:
            napisik = napisik.replace(")", '')
        if '(' in napisik:
            napisik = napisik.replace("(", '')
        if '„' in napisik:
            napisik = napisik.replace("„", '')
        if '”' in napisik:
            napisik = napisik.replace("”", '')
        if ";" in napisik:
            napisik = napisik.replace(";", '')
        if '»' in napisik:
            napisik = napisik.replace("»", '')
        if napisik == 'j' or napisik == 's':
            continue
        if '-' in napisik:
            tabliczka = napisik.split('-')
            for i in range(len(tabliczka)):
                if tabliczka[i] in wszystkie_slowa.keys():
                    licznik[tabliczka[i]] += 1
                    continue
                else:
                    licznik[tabliczka[i]] = 1
                    continue
        elif '/' in napisik:
            tabliczka = napisik.split('/')
            for i in range(len(tabliczka)):
                if tabliczka[i] in wszystkie_slowa.keys():
                    licznik[tabliczka[i]] += 1
                    continue
                else:
                    licznik[tabliczka[i]] = 1
                    continue 
        if napisik in licznik.keys():
            licznik[napisik] += 1
        else:
            licznik[napisik] = 1

def max_wagi(k):
    for el in licznik.keys():
        licznik[el] = licznik[el] * (len(el) ** k)
    for i in range(10):
        maks = max(licznik, key=licznik.get)
        print(maks, licznik[maks])
        del licznik[maks]



max_wagi(3)

