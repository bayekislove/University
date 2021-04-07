from random    import randint

cardsFigurant = ['A', 'K', 'Q', 'J']
colors = [ '♠', '♥', '♦', '♣' ]

def getBlotkarz():
    ret = set()
    while( len( ret ) < 5 ):
        ret.add( colors[ randint( 0, 3 ) ] + str( randint(7, 10) ) )
    return list(ret)

def getFigurant():
    ret = set()
    while( len(ret) < 5 ):
        ret.add( colors[ randint( 0, 3 ) ] + cardsFigurant[ randint( 0, 3 ) ] )
    return list(ret)

def compareHands( bH, fH ):
    bHdict = { str( x ) : 0 for x in range(2, 11) } #2,3,4,5...10
    fHdict = { cardsFigurant[ x ] : 0 for x in range( 4 ) }#K Q J A

    for card in bH: bHdict[ card[1:] ] += 1
    for card in fH: fHdict[ card[1:] ] += 1 

    bHPairs = { 2: 0, 3: 0, 4: 0 }
    fHPairs = { 2: 0, 3: 0, 4: 0 }
    for card in bHdict: 
        if( int( bHdict[card] > 1 ) ): 
            bHPairs[ int( bHdict[card] ) ] += 1
    for card in fHdict: 
        if( int( fHdict[card] > 1 ) ): 
            fHPairs[ int( fHdict[card] ) ] += 1

    blotkarzFigures = { 2:False, 3:False, 4:False, 5:False, 6:False, 7:False, 8:False }
    figurantFigures = { 2:False, 3:False, 4:False, 5:False, 6:False, 7:False, 8:False }

    bH.sort( key=lambda x: int(x[1:]) )
    bHasStraight = all( ( int( bH[ i ][1:] ) == int( bH[ i+1 ][1:] ) - 1 ) for i in range(4) )
    if( bHasStraight ): 
        blotkarzFigures[5] = True #Figurant can't have straight bc he has 4 possibilities for values with 5 cards to choose
    
    if( all( bH[i][0] == bH[i + 1][0] for i in range(4) ) ): blotkarzFigures[4] = True #colour 
    if( all( bH[i][0] == bH[i + 1][0] for i in range(4) ) ): figurantFigures[4] = True

    if( blotkarzFigures[4] and blotkarzFigures[5] ): return 'b' #blotkarz has poker and wins

    if( bHPairs[4] != 0 ): blotkarzFigures[2] = True #four of a kind
    if( fHPairs[4] != 0 ): figurantFigures[2] = True

    if( bHPairs[2] != 1 and bHPairs[3] != 1 ): blotkarzFigures[3] #full
    if( fHPairs[2] != 1 and fHPairs[3] != 1 ): figurantFigures[3] #full

    if( bHPairs[3] != 0 ): blotkarzFigures[6] = True
    if( fHPairs[3] != 0 ): figurantFigures[6] = True

    if( bHPairs[2] != 0 ): blotkarzFigures[ 9 - bHPairs[2] ] = True
    if( fHPairs[2] != 0 ): figurantFigures[ 9 - fHPairs[2] ] = True

    for i in range(2, 9):
        if( blotkarzFigures[i] and figurantFigures[i] or (not blotkarzFigures[i] and not figurantFigures[i]) ):
            continue
        return 'b' if blotkarzFigures[i] else 'f'

    for i in range(2, 9):
        if( figurantFigures[i] ): return 'f'

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
findProbability()