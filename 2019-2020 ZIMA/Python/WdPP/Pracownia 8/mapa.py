from random import randint
from turtle import *

tracer(0, 1)

def zapelnij_macierz():
    wysokosci = []
    for i in range(100):
        linia = []
        for k in range(100):
            linia.append(0)
        wysokosci.append(linia)
    return wysokosci

def zapelnij_wzgorzami():  ### w tej funkcji chodzi o to, zeby wylosowac wzgorza(wysokie punkty). 
    pole = zapelnij_macierz()   #Przyjmijmy, ze ich wysokosc bedzie wahacc sie od 300 do 500 mnpm
    for i in range(500):
        a = randint(0, 99)
        b = randint(0, 99)
        pole[a][b] = randint(400, 3000)
    return(pole)

def zapelnij_cala_macierz():
    pole = zapelnij_wzgorzami()
    for liczba in range(15000):        
        i = randint(0, 99)
        k = randint(0, 99)
        if(pole[i][k] == 0):
            if(k == 0) and (i == 0):
                pole[i][k] = int((pole[i+1][k] + pole[i][k+1] + pole[i+1][k+1]) / 3)
            elif(k == 0) and (i == 99):
                pole[i][k] = int((pole[i-1][k] + pole[i][k+1] + pole[i-1][k+1]) / 3)
            elif(k == 99) and (i == 99):
                pole[i][k] = int((pole[i][k-1] + pole[i-1][k] + pole[i-1][k-1]) / 3)
            elif(k == 99) and (i == 0):
                pole[i][k] = int((pole[i][k-1] + pole[i+1][k] + pole[i+1][k-1]) / 3)
            elif(k == 0):
                pole[i][k] = int((pole[i+1][k] + pole[i+1][k+1] + pole[i][k+1] + pole[i-1][k+1] + pole[i-1][k]) / 5)
            elif(i == 0):
                pole[i][k] = int((pole[i][k-1] + pole[i+1][k-1] + pole[i+1][k] + pole[i+1][k+1] + pole[i][k+1]) / 5)
            elif(k == 99):
                pole[i][k] = int((pole[i+1][k] + pole[i+1][k-1] + pole[i][k-1] + pole[i-1][k-1] + pole[i-1][k]) / 5)
            elif(i == 99):
                pole[i][k] = int((pole[i][k-1] + pole[i-1][k-1] + pole[i-1][k] + pole[i-1][k+1] + pole[i][k+1]) / 5)
            else:
                sum_up = pole[i+1][k-1] + pole[i+1][k] + pole[i+1][k+1]
                sum_rl = pole[i][k-1] + pole[i][k+1]
                sum_dn = pole[i-1][k-1] + pole[i-1][k] + pole[i-1][k+1]
                pole[i][k] = int((sum_up + sum_rl + sum_dn) / 7)
    return pole

def kwadrat():
    for i in range(4):
        fd(5)
        lt(90)
    fd(5)

def wracaj(k, bok):
    up()
    rt(180)
    fd(k)
    rt(90)
    fd(bok)
    rt(90)
    down()

def rysuj_mape():
    pole = zapelnij_cala_macierz()
    up()
    goto(-250, -230)
    down()
    for i in range(len(pole)):
        for k in range(len(pole[i])):
            if pole[i][k] < 70:
                kolorek = 'green'
            elif (pole[i][k] > 70) and (pole[i][k] <= 300):
                kolorek = 'yellow'
            elif (pole[i][k] > 300) and (pole[i][k] <= 600):
                kolorek = 'orange'
            elif pole[i][k] > 600:
                kolorek = 'red'
            fillcolor(kolorek)
            pencolor(kolorek)
            begin_fill()
            kwadrat()
            end_fill()
        wracaj(5 * len(pole[i]), 5)

rysuj_mape()
input()
