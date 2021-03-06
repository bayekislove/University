from math import prod
from time import time

def place( blocks, total ):
    if not blocks: 
        return {"-" * total}
    if blocks[0] > total: 
        return {}

    rBs = total-blocks[0] #rBs = 2 means possible rBing indexes are [0,1,2]
    if len(blocks)==1: #this is special case
        return { ( "." * i + "#" * blocks[0] + "." * (rBs-i) ) for i in range( rBs+1 ) }

    ans = set()
    for i in range(total-blocks[0]): #append current solutions
        for sol in place(blocks[1:],rBs-i-1): #with all possible other solutions
            ans.add( "." * i + "#" * blocks[0] + "." + sol )
    return ans

def gen_possibilities( rowNum, rowsInfo, colsNum ):
    return [ place( rowsInfo[i], colsNum ) for i in range( rowNum ) ]

def formatOutput( tab ):
    out = ''
    for line in tab:
        for char in line:
            out += char
        out += '\n'
    return out

def surePossibility( poss, lth ):
    a = [ set() for _ in range( lth ) ]
    for pos in poss:
        for i in range( len( pos ) ):
              a[i].add( pos[i] )
    return a ##returns what possible fields are to put

def minimizePossibilities( rowPoss, colsPoss, colsNum, rowsNum ):
    nextIter = True
    while( nextIter ):
        nextIter = False
        for rowIdx in range( len( rowPoss ) ): #for every row
            rowPositPoss = surePossibility( rowPoss[rowIdx], colsNum ) # we find out if there is only one possibility for char

            for coll in range( len( rowPositPoss ) ): #we check on every char in this row
                if( len( rowPositPoss[coll] ) == 1 ): #if there is only possibility
                    ( char, ) = rowPositPoss[coll]    #we cross out every other possibility
                    toRemove = set()
                    for p in colsPoss[coll]: #we check every possibility for column
                        if( p[rowIdx] != char ):
                            toRemove.add( p )
                            nextIter = True
                    for delete in toRemove:
                        colsPoss[coll].remove( delete )

        for colIdx in range( len( colsPoss ) ):
            colPositPoss = surePossibility( colsPoss[colIdx], rowsNum )

            for roww in range( len( colPositPoss ) ):
                if ( len( colPositPoss[roww] ) == 1 ):
                    (char, ) = colPositPoss[roww]
                    toRemove = set()
                    for p in rowPoss[roww]:
                        if( p[colIdx] != char ):
                            toRemove.add( p )
                            nextIter = True
                    for delete in toRemove:
                        rowPoss[roww].remove( delete )
        if( any( [len(x) == 0 for x in rowPoss] ) or any( len(x) == 0 for x in colsPoss ) ):
            return False #ta kombinacja jest sprzeczna => nie da rozwiązania

    if( all( [len(x) == 1 for x in rowPoss] ) ):
        return ( True, rowPoss ) #mamy tylko jedno przypisanie do węzła => to rozwiązanie

    return ( rowPoss, colsPoss )

def backtracking( prev, curr, next, i, colsPoss ):
    if i > maxDepth:
        return False
    for poss in curr:
        nextToEdit = [ { y for y in x } for x in next ]
        colsToEdit = [ { y for y in x } for x in colsPoss ]
        res = minimizePossibilities( prev + [{poss}] + nextToEdit, colsToEdit, bColsNum, bRowsNum )
        if res == False:
            continue
        if res[0] == True:
            return res[1]

        a = prev + [{poss}]
        b = res[0][i]
        c = res[0][(i+1):]
        res = backtracking( a, b , c , i + 1, res[1] )
        if res != False:
            return res
    return False


if __name__ == '__main__':
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

        bRowsNum = rows
        bColsNum = cols
        backtracking.rows = rowsInp
        maxDepth = rows

        r = gen_possibilities( rows, rowsInp, cols )
        c = gen_possibilities( cols, colsInp, rows )
        (rB, cB) = minimizePossibilities( r, c, cols, rows )

        result = backtracking( [], rB[0], rB[1:], 1, cB )
        out.write( formatOutput( result ) )