#postarajmy sie zrobic te procedury abstrakcyjnymi

def it_fact(k): #implementacja iteracyjna, wybierz sobie, ktora wolisz (iteracyjna jest minimalnie szybsza)
    output = 1
    for i in range(2, k + 1):
        output = output * i
    return output

def rec_fact(k):
    if k == 1:
        return 1
    return k * rec_fact(k - 1)

def accumulate_facts(last):
    tab = [1] #robimy to po to, zeby nie musiec brac tab[indeks-1] i potencjalnie wpakowywac sie w outofrange; 0! = 1
    for k in range(1, last + 1):
        tab.append(it_fact(k))
    return tab

def find_exceeders(start, end, limit):
    counter = 0
    factorials_tab = accumulate_facts(end)
    for n in range(1, end + 1):
        for k in range(1, n + 1):
            if factorials_tab[n] / (factorials_tab[k] * factorials_tab[n - k]) > limit:
                counter += 1
    return counter

print(find_exceeders(1, 100, 1000000))