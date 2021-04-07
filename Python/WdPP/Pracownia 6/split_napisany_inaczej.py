def podziel(s):
    napis = str(s)
    po_podzieleniu = []
    i = 0
    while(i < len(napis)):
        wyraz = []
        if(napis[i] == " "):
            i += 1
            continue
        if(napis[i] != " "):
            wyraz.append(napis[i])
            i += 1
            while(napis[i] != " "):
                wyraz.append(napis[i])
                i += 1
                if(i == len(s)):
                    break
        if(i == len(s)):
            po_podzieleniu.append(''.join(wyraz))
            break
        if(napis[i] == " "):
            i += 1
            po_podzieleniu.append(''.join(wyraz))
    print(po_podzieleniu)

podziel(" Ala ma    aa kota     ")
podziel("A Set is an unordered collectioge")