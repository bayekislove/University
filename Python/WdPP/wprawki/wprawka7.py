from itertools import permutations 

a = []

liczby = "0123456789"

for literka in liczby:
    a.append(int(literka))

def permutacje(napis):
    return list(permutations(napis))


