import matplotlib.pyplot as plt

def fact(n):
    return 1 if(n == 0 or n == 1) else n*fact(n-1)

def newton(n, k):
    return fact(n) / (fact(k) * fact(n-k))

def bern(n, k, t):
    return newton(n, k) * (t ** k) * ((1-t)**(n-k))

punkty = [(39.5, 10.5), (30, 20), (6, 6), (13, -12), (63, -12.5), (18.5, 17.5), (48, 63),
          (7, 25.5), (48.5, 49.5), (9, 19.5), (48.5, 35.5), (59, 32.5), (56, 20.5)]

wagi = (1, 2, 3, 2.5, 6, 1.5, 5, 1, 2, 1, 3, 5, 1)
wagi2 = (2, 4, 6, 5, 12, 2, 10, 2, 4, 2, 6, 10, 2)

def bezier(n, t):
    mianownik = sum(bern(n, i, t)*wagi[i] for i in range(0, n))

    zwrotX = sum(punkty[i][0] * bern(n, i, t)*wagi[i] for i in range(0, n))
    zwrotY = sum(punkty[i][1] * bern(n, i, t)*wagi[i] for i in range(0, n))

    return (zwrotX/mianownik, zwrotY/mianownik)

def drawBezier():
    X = [None] * 1000
    Y = [None] * 1000
    for i in range(0, 1000):
        X[i] = bezier(13, i / 1000)[0]
        Y[i] = bezier(13, i / 1000)[1]
    plt.plot(X, Y)
    plt.show()

drawBezier()