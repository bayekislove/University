from losowanie_fragmentow import losuj_fragment

def losuj_haslo(n):
    length = n
    while(length!=0):
        f = losuj_fragment()
        if(length == 2):
            while(len(f)!=2):
                f = losuj_fragment()
        elif(length == 3):
            while(len(f)!=3):
                f = losuj_fragment()
        elif(length == 4):
            while((len(f)!=2) or (len(f)!=4)):
                f = losuj_fragment()
        length = length - len(f)
        print(f, end="")
    print()

for i in range(10):
    losuj_haslo(8)
for i in range(10):
    losuj_haslo(12)