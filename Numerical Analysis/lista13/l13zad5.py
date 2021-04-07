import math

def romberg_approx(measur_err, function, a, b):

    def calculate_romberg(n, m):
        if m != 0:
            return romberg_tab[n][m-1] + ((romberg_tab[n][m-1] - romberg_tab[n-1][m-1]) / ((4 ** m) - 1))
        else:
            temp_sum = 0
            for i in range(1, 2**(n-1) + 1):
                temp_sum += function(a + (2*i - 1) * h)
            return (romberg_tab[n-1][0] / 2) + h * temp_sum

    romberg_tab = []
    h = b - a
    romberg_tab.append( [ h*(function(a) + function(b)) / 2 ] ) #dodajemy pierwszy wyraz R(0,0)
    k = 1

    while k <= 16:
        h = h / 2
        romberg_tab.append([]) #dodajemy kolejny wiersz R(k, ...)
        romberg_tab[k].append( calculate_romberg(k, 0) ) #dodajemy wyraz R(k, 0)

        for i in range(1, k+1):
            romberg_tab[k].append( calculate_romberg(k, i) )
            if abs( romberg_tab[k][i] - romberg_tab[k-1][i-1] ) < measur_err:
                return romberg_tab[k][i]

        k += 1
        
    print( romberg_tab[16][ len(romberg_tab[16]) -1 ] )

def a(x):
    return 2021*x*x*x*x*x - 2020*x*x*x*x + 2019*x*x

def b(x):
    return 1 / ( 1 + 25*x*x )

def c(x):
    return math.sin(7*x - 2) / x

romberg_approx(0, a, -1, 2)
romberg_approx(0, b, -2, 2)
romberg_approx(0, c, 2, 3*math.pi)