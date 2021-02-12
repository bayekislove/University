def numsum(num):
    suma = 0
    for _ in range(len(str(num))):
        suma += num % 10
        num = num // 10
    return suma

def searcher():
    dobre = []
    while(len(dobre) < 40):
        for i in range(2, 100):
            for k in range(2, 25):
                if numsum(i ** k) == i and i**k > 10:
                    if i**k not in dobre:
                        dobre.append(i**k)
    return sorted(dobre)

print(searcher()[29])