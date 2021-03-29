from collections import deque

def findAllTargets( board ):
    ret = set()
    for i in range( len(board) ):
        for j in range( len(board[i]) ):
            if( board[i][j] in { '*', '+', 'G' } ):
                ret.add( (i, j) )
    return ret

def findStorageman( board ):
    for i in range( len(board) ):
        for j in range( len(board[i]) ):
            if( board[i][j] in { 'K', '+' } ):
                return (i, j)

def findBoxes( board ):
    ret = set()
    for i in range( len(board) ):
        for j in range( len(board[i]) ):
            if( board[i][j] in { 'B', '*' } ):
                ret.add( (i, j) )
    return ret

def boxesToPull( storageman, board, boxesPositions ):
    ( sRow, sCol ) = storageman
    boardsToPull = set()

    for i in range(4): #skrzynka musi być na polu które chcemy przesunąć, nie możemy przesunąć jej na inną skrzynkę albo na ścianę
        (rDiff, cDiff) = storagemanDirections[i]
        if (( (sRow + rDiff, sCol + cDiff) in boxesPositions )  and 
           ( board[sRow + 2*rDiff][sCol + 2*cDiff] != 'W' ) and
           ( (sRow + 2*rDiff, sCol + 2*cDiff) not in boxesPositions )):
             boardsToPull.add( (sRow + rDiff, sCol + cDiff, i) )
    return boardsToPull

def generateNewSokobanStates( storageman, board, boxesPos ):
    ( sRow, sCol ) = storageman
    boxesPositions = boxesPos.copy()
    newStates = set()
    for ( row, col, direction ) in boxesToPull( storageman, board, boxesPositions ):
        newStates.add( (moveStorageman(sRow, sCol, direction), 
                       frozenset(pullBox( row, col, direction, boxesPositions )),  
                       storagemanStrDirections[direction] ) )
    
    for ( pos, direction ) in storagemanMovePossibilities( storageman, boxesPositions, board ):
        toAdd = ( pos, frozenset(boxesPositions), storagemanStrDirections[direction] )
        newStates.add( toAdd )
    return newStates

def storagemanMovePossibilities( storageman, boxes, board ): #tutaj wpadają tylko ruchy które nie przemieszczają skrzynek!
    ( sRow, sCol ) = storageman
    newPositions = set()
    for ichuj in range(4): 
        (rDiff, cDiff) = storagemanDirections[ichuj]
        if( board[rDiff+sRow][sCol+cDiff] != 'W' and ( (rDiff+sRow, sCol+cDiff) not in boxes ) ):
            newPositions.add( ( (rDiff+sRow, sCol+cDiff), ichuj ) )
    return newPositions

def moveStorageman( sRow, sCol, direction ):
    (rDiff, cDiff) = storagemanDirections[direction]
    return (sRow + rDiff, sCol + cDiff)

def pullBox( bRow, bCol, direction, boxesPos ):
    boxesPositions = { x for x in boxesPos }
    (rDiff, cDiff) = storagemanDirections[direction]
    boxesPositions.remove( (bRow, bCol) )
    boxesPositions.add( (bRow+rDiff, bCol+cDiff) ) 
    return boxesPositions

storagemanDirections = [ (1, 0), (0, -1), (-1, 0), (0, 1) ] # [down, left, up, right]
storagemanStrDirections = ['D', 'L', 'U', 'R']

def sokobanBFS( startPosition, boxesPositions, goals, board ):
    bfs = deque()
    bfs.append( ( startPosition, boxesPositions, '' ) )

    remembered = set()
    
    while( len( bfs ) > 0 ):
        ( currPos, currBoxes, history ) = bfs.popleft()
        print( currPos, currBoxes, history )
        remembered.add( (currPos, currBoxes) )
        for (stor, bxs, dir) in generateNewSokobanStates( currPos, board, boxesPositions ):

            for x in bxs:
                flague = x in goals
                if( not flague ):
                    break
            if( flague ):
                return history + dir

            if( (stor, bxs) not in remembered ):
                bfs.append( (stor, bxs, history + dir) )

def zad2():
    with open( 'zad_output.txt', 'w' ) as out:
        with open( 'zad_input.txt' ) as inp:
            rows = []
            for line in inp:
                rows.append( line.strip('\n') )

            sokoban = findStorageman( rows )
            boxes = findBoxes( rows )
            targets = findAllTargets( rows )
            print( sokobanBFS( sokoban, frozenset(boxes), targets, rows ) )

if __name__ == '__main__':
    zad2()