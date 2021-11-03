from math import ceil, sqrt
from time import time

def isprime(num):
    if num < 2:
        return False
    for i in range(2, ceil(sqrt(num))+1):
        if num % i == 0:
            return False
    return True

def pierwsze_imperatywna(n):
    ret = []
    i = 2
    while i <= n:
        if isprime(i):
            ret.append(i)
        i += 1
    return ret

def pierwsze_skladana(n):
    return [ i for i in range(2, n+1) if isprime(i) ]

def pierwsze_funkcyjna(n):
    return list(filter(isprime, range(2, n+1)))

if __name__ == '__main__':
    funclist = [pierwsze_funkcyjna, pierwsze_skladana, pierwsze_imperatywna]
    for func in funclist:
        for i in range(100000*3, 300000*3, 20000*3):
            start = time()
            func(i)
            print(f'Czas wykonania {func.__name__} dla {i} to: {round(time() - start, 4)}')
        