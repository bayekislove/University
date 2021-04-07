from ulamki import dodaj_ulamki, nowy_ulamek, odejmij_ulamki, podziel_ulamki, przemnoz_ulamki
from figury import przesun, nowe_kolo, nowy_kwadrat, nowy_trojkat, pole, sumapol

a = nowy_ulamek(4,8)
b = nowy_ulamek(2,8)
c = nowy_ulamek(-2, 6)
d = nowy_ulamek(1.7, -2)
print(a, b, c, d)
print(dodaj_ulamki(a, b))
print(odejmij_ulamki(a, b))
print(przemnoz_ulamki(a,b))
print(podziel_ulamki(a,b))

print()
print()
print()

kolo = nowe_kolo(0, 0, 3)
print(kolo)
print(przesun(kolo, 2, 3))
print(pole(kolo))
kwadrat = nowy_kwadrat(2, 4, 5)
print(przesun(kwadrat, 2, 3))
print(pole(kwadrat))
trojkat = nowy_trojkat(0, 2, 2, 0)
print(pole(trojkat))
print(przesun(trojkat, 1, 0))
print(sumapol([trojkat,kolo,kwadrat]))

