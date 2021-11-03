from time import time

def czy_doskonala(n):
    return sum(i for i in range(1, n) if n % i == 0) == n

def doskonale_imperatywna(n):
    ret = []
    i = 2
    while i <= n:
        if czy_doskonala(i):
            ret.append(i)
        i += 1
    return ret

def doskonale_skladana(n):
    return [ i for i in range(2, n+1) if czy_doskonala(i) ]

def doskonale_funkcyjna(n):
    return list(filter(czy_doskonala, range(2, n+1)))

if __name__ == '__main__':
    funclist = [doskonale_funkcyjna, doskonale_skladana, doskonale_imperatywna]
    for func in funclist:
        for i in range(100000, 300000, 50000):
            start = time()
            func(i)
            print(f'Czas wykonania {func.__name__} dla {i} to: {time() - start}')

print(czy_doskonala(28))
print(czy_doskonala(8128))
print(czy_doskonala(8130))  