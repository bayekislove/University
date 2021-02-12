romans = [["I", 1],["IV",4],["V",5],["IX",9],["X",10],["XL",40],["L",50],["XC",90],["C",100],["CD",400],["D",500],["CM",900],["M",1000]]
romans_dict = dict(romans)
def arabictoroman(arabic):
    romaned = ""
    i = len(romans) - 1
    while(i >= 0):
        if arabic - romans[i][1] >= 0:
            arabic = arabic - romans[i][1]
            romaned += romans[i][0]
            i += 1
        i -= 1
    return romaned

def romantoarabic(roman):
    i = 0
    arabic = 0
    while(i <= len(roman) - 1):
        if i == len(roman) - 1:
            arabic += romans_dict[roman[i]]
            return arabic
        if romans_dict[roman[i]] < romans_dict[roman[i+1]]:
            arabic += romans_dict[roman[i] + roman[i+1]]
            if i == len(roman) - 1:
                return arabic
            i += 1
        else:
            arabic += romans_dict[roman[i]]
        i += 1
    return arabic

def find_difference():
    roznica = 0
    for line in open("roman.txt",encoding="utf-8"):
        line = line[:len(line) - 1] #omijamy przez to znak nowej linii ;)
        roznica += len(line) - len(arabictoroman(romantoarabic(line)))
    return roznica

print(find_difference())