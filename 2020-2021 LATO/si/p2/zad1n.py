from random   import   randint, choice
from zad1     import   minimizePossibilities, checker, gen_permutations

def place( blocks, total ):
    if not blocks: 
        return {"0" * total}
    if blocks[0] > total: 
        return {}

    starts = total-blocks[0] #starts = 2 means possible starting indexes are [0,1,2]
    if len(blocks)==1: #this is special case
        return { ( "0" * i + "1" * blocks[0] + "0" * (starts-i) ) for i in range( starts+1 ) }

    ans = set()
    for i in range(total-blocks[0]): #append current solutions
        for sol in place(blocks[1:],starts-i-1): #with all possible other solutions
            ans.add( "0" * i + "1" * blocks[0] + "0" + sol )
    return ans

def gen_possibilities( rowNum, rowsInfo, colsNum ):
    return [ place( rowsInfo[i], colsNum ) for i in range( rowNum ) ]

def createRandomTab( rows, cols, cRows, cCols ):
    tab = [ [ str(randint(0, 1)) for i in range( cols ) ] for i in range( rows ) ]
    tabT = [ [ tab[i][j] for i in range( rows ) ] for j in range( cols ) ]
    return (tab, tabT)

def solve( rows, cols, cRows, cCols ):
    (tab, tabT) = createRandomTab( rows, cols, cRows, cCols )

    corrRows = [ optDist( ''.join( tab[i] ), cRows[i] ) for i in range( rows ) ]
    corrCols = [ optDist( ''.join( tabT[i] ), cCols[i] ) for i in range( cols ) ]

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

            tryMatch = optDist( ''.join( tab[rowIdx] ), cRows[ rowIdx ] ) + optDist( ''.join( tabT[i] ), cCols[i] )
            if( tryMatch < best[1] ):
                best = ( i, tryMatch )

            changeTabs( rowIdx, i )
        return best[0]

    def chooseBestPixelCol( colIdx ): 
        best = ( 0, rows )
        for i in range( rows ):
            changeTabs( i, colIdx )

            tryMatch = optDist( ''.join( tabT[colIdx] ), cCols[ colIdx ] ) + optDist( ''.join( tab[i] ), cRows[i] )
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

        corrRows[i] = optDist( ''.join( tab[i] ), cRows[i] )
        corrCols[j] = optDist( ''.join( tabT[j] ), cCols[j] )

        if( count % 10000000 == 0 ):
            (tab, tabT) = createRandomTab( rows, cols, cRows, cCols )
            corrRows = [ optDist( ''.join( tab[i] ), cRows[i] ) for i in range( rows ) ]
            corrCols = [ optDist( ''.join( tab[i] ), cCols[i] ) for i in range( cols ) ]
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

def counter( string ):
    count = []
    prev = 0
    for i in range( len( string ) ):
        if( string[i] == '1' ):
            prev += 1
        elif( prev != 0 ):
            count.append( prev )
            prev = 0
    if( string[ len(string) - 1 ] == '1' ):
        count.append( prev )
    return count

def bitsDifferent( z, y ):
    x = int( z, 2 ) ^ int( y, 2 )
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555))
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333))
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f))
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff))
    return (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff))

def optDist( string, correct ):
    return min( [bitsDifferent( string, guess ) for guess in correct] )

def zad1n():
    with open( 'zad_output.txt', 'w' ) as out:
        with open( 'zad_input.txt' ) as inp:
            content = inp.read().splitlines()
        rows = int( content[0].split(' ')[0] )
        cols = int( content[0].split(' ')[1] )
        rowsInp = [0] * rows
        colsInp = [0] * cols
        for i in range( 1, rows + 1 ):
                rowsInp[i - 1] = list( map( int, content[i].split( ' ' ) ) )
        for i in range( rows + 1, len( content ) ):
                colsInp[i - rows - 1 ] = list( map( int, content[i].split( ' ' ) ) )
        # rows = 3
        # cols = 3
        # rowsInp = [[1], [1], [1]]
        # colsInp = [[1], [1], [1]]
        r = gen_possibilities( rows, rowsInp, cols )
        c = gen_possibilities( cols, colsInp, rows )
        (rB, cB) = minimizePossibilities( r, c, cols, rows )

        rowProd = 1
        for row in r:
            rowProd *= len(row) 

        if( rowProd < 0 ):
            result = checker( gen_permutations( rB ), colsInp, cols )
        else:
            result = solve( rows, cols, rB, cB )
        #print( time() - start )
        out.write( formatOutput( result ) )

zad1n()