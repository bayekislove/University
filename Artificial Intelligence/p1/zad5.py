from random import getrandbits, randint
from zad4   import optDist

def createRandomTab( rows, cols ):
    tab = [ [ str( getrandbits(1) ) for i in range( cols )] for j in range( rows ) ]
    tabT = [ [ tab[i][j] for i in range( rows ) ] for j in range( cols ) ]
    return (tab, tabT)

def solve( rows, cols, rowsInp, colsInp ):
    (tab, tabT) = createRandomTab( rows, cols )

    corrRows = [ optDist( ''.join( tab[i] ), rowsInp[i] ) for i in range( rows ) ]
    corrCols = [ optDist( ''.join( tabT[i] ), colsInp[i] ) for i in range( cols ) ]

    def chooseRow( ): #returns index of chosen rowzz
        ( badLine, line ) = ( [ i for i in range( rows ) if corrRows[i] > 0 ], 'r')
        if( len( badLine ) == 0 ):
            ( badLine, line ) = ( [ i for i in range(cols) if corrCols[i] > 0 ], 'c' )
        return ( badLine[ randint( 0, len(badLine) - 1 ) ], line )

    def changeTabs( i, j ):
        newPixel = '0' if int( tab[ i][ j ] ) else '1'
        tab[ i ][ j ] = newPixel
        tabT[ j ][ i ] = newPixel

    def chooseBestPixelRow( rowIdx ): #we return index of change in row ( column to change in given row )
        best = ( 0, cols )
        for i in range( cols ):
            changeTabs( rowIdx, i )

            tryMatch = optDist( ''.join( tab[rowIdx] ), rowsInp[ rowIdx ] ) + optDist( ''.join( tabT[i] ), colsInp[i] )
            if( tryMatch < best[1] ):
                best = ( i, tryMatch )

            changeTabs( rowIdx, i )
        return best[0]

    def chooseBestPixelCol( colIdx ): 
        best = ( 0, rows )
        for i in range( rows ):
            changeTabs( i, colIdx )

            tryMatch = optDist( ''.join( tabT[colIdx] ), colsInp[ colIdx ] ) + optDist( ''.join( tab[i] ), rowsInp[i] )
            if( tryMatch < best[1] ):
                best = ( i, tryMatch )

            changeTabs( i, colIdx )
        return best[0]

    count = 1
    while ( any( corrRows[i] != 0 for i in range( rows ) ) or 
            any( corrCols[i] != 0 for i in range( cols ) )  ):
        
        ( i, line )  = chooseRow()
        j = chooseBestPixelRow( i ) if line == 'r' else chooseBestPixelCol( i )
        
        if( line == 'r' ): 
            changeTabs( i, j )
        else: 
            changeTabs( j, i )

        corrRows[i] = optDist( ''.join( tab[i] ), rowsInp[i] )
        corrCols[j] = optDist( ''.join( tabT[j] ), colsInp[j] )

        if( count % 10000 == 0 ):
            (tab, tabT) = createRandomTab( rows, cols )
            corrRows = [ optDist( ''.join( tab[i] ), rowsInp[i] ) for i in range( rows ) ]
            corrCols = [ optDist( ''.join( tab[i] ), colsInp[i] ) for i in range( cols ) ]
        count += 1

    return tab

def formatOutput( tab ):
    out = ''
    for line in tab:
        for char in line:
            if char == '1':
                out += '#'
            else:
                out += '.'
        out += '\n'
    return out

with open( 'zad5_output.txt', 'w' ) as out:
    with open( 'zad5_input.txt' ) as inp:
        content = inp.read().splitlines()
    rows = int( content[0].split(' ')[0] )
    cols = int( content[0].split(' ')[1] )
    rowsInp = [0] * rows
    colsInp = [0] * cols
    for i in range( 1, rows + 1 ):
        rowsInp[i - 1] = int(content[i])
        colsInp[i - 1] = int(content[rows + i])
    out.write( formatOutput( solve( rows, cols, rowsInp, colsInp ) ) )

print( formatOutput( solve(7,7, [7,7,7,7,7,7,7], [7,7,7,7,7,7,7] ) ) )
print( formatOutput( solve(7,7, [2,2,7,7,2,2,2], [2,2,7,7,2,2,2] ) ) )
print( formatOutput( solve(7,7, [2,2,7,7,2,2,2], [4,4,2,2,2,5,5] ) ) )
print( formatOutput( solve(7,7, [7,6,5,4,3,2,1], [1,2,3,4,5,6,7] ) ) )
print( formatOutput( solve(7,7, [7,5,3,1,1,1,1], [1,2,3,7,3,2,1] ) ) )