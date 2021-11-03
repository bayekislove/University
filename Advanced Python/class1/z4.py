from random import random

def experiment(consecSide):
    totalDrawns = 0
    lastDrawn  = None
    lastDrawnCounter = 0
    while lastDrawnCounter < consecSide:
        totalDrawns += 1
        draw = round(random())
        if lastDrawn == draw:
            lastDrawnCounter += 1
        else: 
            lastDrawn = draw
            lastDrawnCounter = 1
    return totalDrawns

def z4(N, consecSide):
    drawns = 0
    for _ in range(N):
        drawns += experiment(consecSide)
    return drawns / N

print(z4(1, 6))