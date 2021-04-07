from ceasar import caesar

polskie_slowa = {}

for linia in open('slowa.txt', encoding='utf-8'):
    polskie_slowa[(linia[:-1]).lower()] = len((linia[:-1]).lower())

def ceasar_words(k):
    for slowo1 in polskie_slowa:
        for slowo2 in polskie_slowa:
            if polskie_slowa[slowo1] == polskie_slowa[slowo2]:
                for i in range(len(slowo1)):
                    if slowo1[i] == caesar(slowo2[i], k):
                        continue
                    else:
                        break
                    print(slowo1 + " " + slowo2 + " "+ str(k), sep=" ")

for i in range(1, 33):
    ceasar_words(i)


print(caesar('kot', 3))
    