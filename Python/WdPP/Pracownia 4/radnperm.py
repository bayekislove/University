from random import choice, randint

def randperm(n):
    kolejne_liczby = []
    for i in range(n):
            kolejne_liczby.append(i)
    permutacja = []
    while(len(kolejne_liczby) > 0):
        wybor = choice(kolejne_liczby)
        permutacja.append(wybor)
        kolejne_liczby.remove(wybor)
    print(permutacja) 

randperm(3)
randperm(9)
randperm(5)
randperm(8)