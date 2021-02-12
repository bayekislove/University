import time
def dobre_slowo(p):
    slowo = str(p)
    if any(znak in slowo[-1] for znak in 'ćśąę'):
        return False
    elif "cie" in slowo or ('śmy') in slowo or 'cię' in slowo:
        return False
    elif ('iąt' in slowo) or ('ięt' in slowo):
        return False
    elif 'ąc' in slowo or 'ęc' in slowo:
        return False
    elif 'ież' in slowo:
        return False
    elif 'rż' in slowo:
        return False
    elif ('liby' in slowo) or ('bym' in slowo) or ('byś' in slowo):
        return False
    elif ('łem' in slowo) or ('łam' in slowo) or ('łaś' in slowo) or ('łeś' in slowo):
        return False
    else:
        return True

def dlugosc_slowa(k, dlugosc):
    if len(k) == dlugosc:
        return True 

def wyszukaj_kandydatow():
    zbior_slow = dict()
    for x in open('slowa.txt', encoding='utf-8'):
        sloweczko = x[:len(x)-1]
        zbior_slow[sloweczko] = len(sloweczko) 
    print(zbior_slow)
    return zbior_slow

def sprawdzacz():
    dlugosc = 2
    licznik = 1
    ile_slow = 0
    zbior_slow = wyszukaj_kandydatow()
    ##while(licznik > 0):
     ##   licznik = 0
       # for slowko in zbior_slow:
        #    temp_slowo = []
         #   for i in range(len(slowko)):
          #      temp_slowo.append(slowko[-1-i])
           # koko = ''.join(temp_slowo)
            #if koko in zbior_slow:
             #   print("Znaleziono parę słów odwrotnych: " + koko + "  " + slowko)
              #  if koko == slowko:
               #     zbior_slow.remove(slowko)
                #    licznik += 1
                 #   continue
               # zbior_slow.remove(koko)
                #zbior_slow.remove(slowko)
                #licznik += 2
            #else:
             #   zbior_slow.remove(slowko)
        #dlugosc += 1
        #ile_slow += licznik
    for el in zbior_slow:
        if dict(el) == 2:
            print(el)
wyszukaj_kandydatow()
        

