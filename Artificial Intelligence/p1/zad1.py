def genPossibleMovesKing( king ):
    kCol = king[0]
    kRow = king[1]
    guesses = set()
    for i in range(-1, 2):
        for j in range(-1, 2):
            guesses.add( ( ord(kCol) + i, ord( kRow ) + j ) )
    guesses.remove( ( ord(kCol), ord( kRow ) ) )
    return [ chr(x) + chr(y) for (x, y) in guesses if (((x >= 49 and x <= 56) or (x >= 97 and x <= 104 )) and
                                                      ((y >= 49 and y <= 56) or (y >= 97 and y <= 104 ))) ]

def getAllowedMovesKing( kColor, checkedKing, anotherKing, rook ):
    enemy = genPossibleMovesKing( anotherKing )
    if( kColor == 'white' ):
        return [ x for x in genPossibleMovesKing( checkedKing ) if (x not in enemy)
                 and ( x[0] != rook[0] or x[1] != rook[1] ) ]

    return [ x for x in genPossibleMovesKing( checkedKing ) if (x not in enemy )
                and ( ( x == rook and rook not in enemy)  or ( x[0] != rook[0] and x[1] != rook[1] ) ) ]
                                                       
def genPossibleMovesRook( rook, king, anotherKing ):
    rRow = ord( rook[1] )
    rCol = ord( rook[0] )
    guesses = []
    # rookCol -> rightCol 
    for c in range( rCol + 1, ord( 'h' ) + 1 ):
        if ( ( chr( rCol ) + chr( c ) ) != king and (  chr( c ) + chr( rRow ) ) != anotherKing ):
            guesses.append( chr( c ) + chr( rRow ) )
        else:
            break
    for c in range( rCol - 1, ord( 'a' ) - 1, -1 ): # rookCol -> leftCol
        if ( ( chr( rCol ) + chr( c ) ) != king and ( chr( c ) + chr( rRow ) ) != anotherKing ):
            guesses.append( chr( c ) + chr( rRow ) )
        else:
            break
    for r in range( rRow + 1, ord( '8' ) + 1 ): #rookRow -> upRow
        if ( ( chr( rCol ) + chr( r ) ) != king and ( chr( rCol ) + chr( r ) ) != anotherKing ):
            guesses.append( chr( rCol ) + chr( r ) )
        else: 
            break 
    for r in range( rRow - 1, ord( '1' ) - 1, -1 ): #rookRow -> upRow
        if ( ( chr( rCol ) + chr( r ) ) != king and ( chr( rCol ) + chr( r ) ) != anotherKing ):
            guesses.append( chr( rCol ) + chr( r ) )
        else: 
            break 
    return guesses

def getFastestCheckmate( whoMoves, wK, wR, bK ):
    if( getAllowedMovesKing( 'black', bK, wK, wR ) == [] and ( gBk[0] == guessRook[0] or gBk[1] == guessRook[1] ) ):
        return 0
    toCheck = { (wK, wR, bK, '') }
    remembered = set()
    remembered.add( f'{wK}{wR}{bK}' )
    for i in range( 1, 17 ):
        newToCheck = set()
        if( whoMoves == 'white' ):
            for (gWk, gWr, gBk, msg) in toCheck:

                for guessRook in genPossibleMovesRook( gWr, gWk, gBk ):
                    if( f"{gWk}{guessRook}{gWk}" in remembered ):
                            continue
                    remembered.add( f"{gWk}{guessRook}{gBk}" )

                    pom = getAllowedMovesKing( 'black', gBk, gWk, guessRook )
                    if( pom == [] ): #we omit moves in which killing rook is possible ( thus provoking stalemateS )
                        if( gBk[0] == guessRook[0] or gBk[1] == guessRook[1] ): #mate, stalemate otherwise
                            return ( msg + f'{gWr}{guessRook}', i )

                    elif ( guessRook not in pom ): #if we can kill the rook we dont count that move
                            newToCheck.add( ( gWk, guessRook, gBk, msg + f'{gWr}{guessRook} ' ) )
                    
                for guessKing in getAllowedMovesKing( 'white', gWk, gBk, gWr ):
                    if( f"{guessKing}{gWr}{gWk}" in remembered ):
                            continue
                    remembered.add( f"{guessKing}{gWr}{gBk}" )

                    pom = getAllowedMovesKing( 'black', gBk, guessKing, gWr )
                    if( pom == [] and ( gBk[0] == guessRook[0] or gBk[1] == guessRook[1] ) ):
                            return ( msg + f'{gWk}{guessKing}', i )
                    else:
                        newToCheck.add( ( guessKing, gWr, gBk, msg + f'{gWk}{guessKing} ' ) )
                
        else:
            for (gWk, gWr, gBk, msg) in toCheck:
                for guessKing in getAllowedMovesKing( 'black', gBk, gWk, gWr ):
                    if( (f"{gWk}{gWr}{guessKing}" in remembered) or (guessKing == gWr) ):
                        continue
                    remembered.add( f"{gWk}{gWr}{guessKing}" )
                    newToCheck.add( ( gWk, gWr, guessKing, msg + f'{gBk}{guessKing} ' ) )

        toCheck = newToCheck
        whoMoves = 'black' if whoMoves == 'white' else 'white'

# assert( getFastestCheckmate('white', 'h6', 'a4', 'd4')[1] == 9 ) #9
# assert( getFastestCheckmate('black', 'b4', 'f3', 'e8')[1] == 6 ) #6
# assert( getFastestCheckmate('black', 'a2', 'e4', 'a4')[1] == 8 ) #8
# assert( getFastestCheckmate('white', 'a1', 'e3', 'b7')[1] == 9 ) #9
# assert( getFastestCheckmate('black', 'g8', 'h1', 'c4')[1] == 10 ) #10
# assert( getFastestCheckmate('black', 'h7', 'a2', 'f2')[1] == 6 ) #6

with open('zad1_output.txt', 'w') as outp:
    for line in open('zad1_input.txt', encoding='utf-8'):
        line = line.strip('\n').split(' ')
        outp.write( str( getFastestCheckmate( line[0], line[1], line[2], line[3] )[1] ) + '\n' )