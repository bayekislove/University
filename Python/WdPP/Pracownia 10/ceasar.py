literki = []
for e in "aąbcćdeęfghijklłmnńoóprsśtuwyzźż":
    literki.append(e)
cyferki = []
for i in range(len(literki)):
    cyferki.append(i+1)
alfabet = dict(zip(literki, cyferki))

def caesar(slowo, klucz):
    slowo_zaszyfrowane = []
    try:
        for literka in slowo:
            zaszyfrowany_indeks = int(alfabet[literka]) + int(klucz)
            if zaszyfrowany_indeks > 32:
                zaszyfrowany_indeks -= 32
            zaszyfrowana_literka = literki[zaszyfrowany_indeks - 1]
            slowo_zaszyfrowane.append(zaszyfrowana_literka)
    except KeyError:
        pass
    return ''.join(slowo_zaszyfrowane)

print(caesar('kot', 3))

print([])