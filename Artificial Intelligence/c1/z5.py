from random    import randint
from itertools import combinations

cardsFigurant = ['A', 'K', 'Q', 'J']
colors = [ '♠', '♥', '♦', '♣' ]

def genAllBlotkarzCards():
    return set( colors[i]+str(j) for i in range(4) for j in range(2, 11) )

def genAllBlotkarzHands():
    return list( combinations( genAllBlotkarzCards(), 5 ) )

def genAllFigurantCards():
    return set( colors[i]+cardsFigurant[j] for i in range(4) for j in range(4) )

def genAllFigurantHands():
    return list( combinations( genAllFigurantCards(), 5 ) )

def getBlotkarz():
    ret = set()
    while( len( ret ) < 5 ):
        ret.add( colors[ randint( 0, 3 ) ] + str( randint(2, 10) ) )
    return list(ret)

def getFigurant():
    ret = set()
    while( len(ret) < 5 ):
        ret.add( colors[ randint( 0, 3 ) ] + cardsFigurant[ randint( 0, 3 ) ] )
    return list(ret)

def getScoreBlotkarz( bH ):
    bHdict = { str( x ) : 0 for x in range(2, 11) } #2,3,4,5...10

    for card in bH: bHdict[ card[1:] ] += 1
    bHPairs = { 2: 0, 3: 0, 4: 0 }

    for card in bHdict: 
        if( int( bHdict[card] > 1 ) ): 
            bHPairs[ int( bHdict[card] ) ] += 1

    bH.sort( key=lambda x: int(x[1:]) )

    bHasStraight = all( ( int( bH[ i ][1:] ) == int( bH[ i+1 ][1:] ) - 1 ) for i in range(4) )
    bHasColour = all( bH[i][0] == bH[i + 1][0] for i in range(4) )

    if( bHasStraight and bHasColour ): 
        return 8
    if( bHPairs[4] != 0 ): 
        return 7
    if( bHPairs[2] != 0 and bHPairs[3] != 0 ): 
        return 6 

    if( bHasColour ):
        return 5
    if( bHasStraight ):
        return 4

    if( bHPairs[3] != 0 ):
        return 3

    return bHPairs[2]

def getScoreFigurant( fH ):
    fHdict = { cardsFigurant[ x ] : 0 for x in range( 4 ) } #K Q J A
    for card in fH: fHdict[ card[1:] ] += 1 
    fHPairs = { 2: 0, 3: 0, 4: 0 }
    for card in fHdict: 
        if( int( fHdict[card] > 1 ) ): 
            fHPairs[ int( fHdict[card] ) ] += 1
        
    if( fHPairs[4] != 0 ): 
        return 7
    if( fHPairs[2] != 0 and fHPairs[3] != 0 ): 
        return 6 

    if( fHPairs[3] != 0 ):
        return 3

    return fHPairs[2]

def compareHands( bH, fH ):
    if( getScoreFigurant( fH ) >= getScoreBlotkarz( bH ) ):
        return 'f'
    return 'b'

def findProbability():
    b = 0.0
    f = 0.0
    for i in range( 100000 ):
        cards = getBlotkarz(), getFigurant()
        if( compareHands( cards[0], cards[1] ) == 'f' ):
            f += 1
        else:
            b += 1
    print( b / f )
    
def findProbabilityCwiczenia():
    b = [ getScoreBlotkarz( list(x) ) for x in genAllBlotkarzHands() ]
    f = [ getScoreFigurant( x ) for x in genAllFigurantHands() ]

    bWon = 0.0
    fWon = 0.0

    for fTry in f:
        for bTry in b:

            if( fTry < bTry ):
                bWon += 1.0
            else:
                fWon += 1.0
                
    print( bWon / (fWon + bWon) )

findProbabilityCwiczenia()