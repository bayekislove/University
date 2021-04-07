def pary(n):
    pary = []
    for i in range(n+1):
        for k in range(i+1):
            pary.append([k, i - k])
    print(pary)

pary(3)

def pary_compreh(n):
    pary_liczb = [[k, i - k] for i in range(n+1) for k in range(i+1)]
    return pary_liczb

print(pary_compreh(3))

