from math import floor

def main(s_licznik, s_mianownik, d):
    kandydat = 0  #tu bedziemy przechowywac licznik najbardziej na lewo od inputowanego ulamka
    min_roznica = 1000 #tu bedziemy przechowywac najmniejsza roznice (czyli to determiniuje jak blisko jest nasz ulamek do inputa)
    for i in range(2, d+1): #dla kazdego mozliwego mianownika
        temp_licznik = floor((s_licznik * i - 1) / s_mianownik)
        temp_roznica = (s_licznik / s_mianownik) - (temp_licznik / i)
        if temp_roznica < min_roznica:
            kandydat = temp_licznik
            min_roznica = temp_roznica
    return kandydat
                
print(main(3, 7, 1000000))