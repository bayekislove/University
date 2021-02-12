def usun_nawiasy(s):
    wyraziki = list(str(s))
    koncowa = []
    i = 0
    while(i != len(s)):
        if(wyraziki[i] != "("):
            koncowa.append(wyraziki[i])
            i += 1
            continue
        if(wyraziki[i] == "("):
            i += 1
            while(wyraziki[i] != ")"):
                    i += 1
        if(wyraziki[i] == ")"):
            i += 1
    print(str("".join(koncowa)))


usun_nawiasy("Ala ma (czerwonego) kota!")
usun_nawiasy("prawo( i       ) sprawiedliwosc!")
usun_nawiasy("awdaa(sd)")
usun_nawiasy("awdoabwdpihawpdjaw()  a")
usun_nawiasy("(!)")
