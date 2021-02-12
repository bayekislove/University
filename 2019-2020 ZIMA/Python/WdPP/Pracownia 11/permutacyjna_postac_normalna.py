def pnf(s):
    pnf_zwrot = []
    literka_liczba = {}
    spotkane_literki = 1
    for literka in s:
        if literka not in literka_liczba.keys():
            literka_liczba[literka] = spotkane_literki
            pnf_zwrot.append(str(spotkane_literki))
            spotkane_literki += 1
        else:
            pnf_zwrot.append(str(literka_liczba[literka]))
    slowko = '-'.join(pnf_zwrot)
    return slowko

print(pnf('tata'))
print(pnf('tak'))
print(pnf('indianin'))