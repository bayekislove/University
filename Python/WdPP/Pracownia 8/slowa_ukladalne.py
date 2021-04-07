from random import choice

def slowo_slownik(k):
    literki = {}
    for i in range(len(k)):
        if k[i] in literki.keys():
            literki[k[i]] += 1
        else:
            literki[k[i]] = 1
    return literki


def sprawdzacz(pier, dr): #z pierwszego ukladamy drugie
    pierwsze = slowo_slownik(pier)
    drugie = slowo_slownik(dr)
    if len(pier) < len(dr):
        return False
    else:
        for el in drugie.keys():
            if el not in pierwsze.keys():
                return False
            elif pierwsze[el] < drugie[el]:
                return False
    return True


print(sprawdzacz("lokomotywa", "motyl"))
print(sprawdzacz("lokomotywa", "żak"))