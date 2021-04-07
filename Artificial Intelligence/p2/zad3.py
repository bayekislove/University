from  heapq       import heappop, heappush
from  collections import deque

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

directions = [ (1, 0), (0, -1), (-1, 0), (0, 1) ] # [down, left, up, right]
strDirections = ['D', 'L', 'U', 'R']

def isContained( box, boxes ):
    return any( [ ( box == b ) for (x, b) in boxes ] )

def genBoxPossibilities( box, boxes, board ): #we return position of new box + direction
    ( bR, bC ) = box
    returned = set()
    for i in range( 4 ):
        ( rDiff, cDiff ) = directions[i]
        if( board[ bR - rDiff ][ bC - cDiff ] != 'W' and
            ( not isContained( ( bR - rDiff, bC - cDiff ), boxes ) ) and
            ( board[ bR + rDiff ][ bC + cDiff ] != 'W' ) and 
            ( not isContained( ( bR + rDiff, bC + cDiff ), boxes ) ) ):
                returned.add( ( bR + rDiff, bC + cDiff, i ) )
    return returned

def genAllPossibleNewBoxesPositions( boxess, board ):
    newStates = set()
    for (idx, box) in boxess:
        boxes = { x for x in boxess }
        boxes.remove( (idx, box) )
        possibilities = genBoxPossibilities( box, boxes, board )
        boxes.add( (idx, box) )

        for pos in possibilities:
            ( nR, nC, dir ) = pos
            boxes.remove( ( idx, box ) )
            boxes.add( ( idx, ( nR, nC ) ) )

            newStates.add( ( frozenset(boxes), box, dir ) ) # ( states after box push, pushed box, push direction )
            boxes.remove( ( idx, ( nR, nC ) ) )
            boxes.add( ( idx, box ) )
    return newStates

def sokobanButByBoxes( startPosition, boxes, targets, board ):
    priorityQueque = []
    heappush( priorityQueque, ( 0, boxes , [] ) )

    i = 1
    remembered = set()

    while( len( priorityQueque ) > 0 ):
        ( currCost, currBxsPos, currHistory ) = heappop( priorityQueque )
        remembered.add( frozenset(currBxsPos) )

        for ( newBoxes, movedBox, direction ) in genAllPossibleNewBoxesPositions( currBxsPos, board ):
            if all( [ ( x in targets ) for (syf, x) in newBoxes ] ):
                validation = validateMoves( startPosition, boxes, currHistory + [( movedBox, direction )], board )
                if( validation != False ):
                    return validation

            if( newBoxes not in remembered ):
                heappush( priorityQueque, ( i, newBoxes, currHistory + [( movedBox, direction )] ) )
                i += 1

def sokobanButBy( startPosition, boxes, targets, board ):
    boxesStart = { x for x in boxes }
    boxes = addUniqueness( boxes )
    
    que = deque()
    que.append( ( boxes, [] ) )
    remembered = set()

    while( len( que ) > 0 ):
        (  currBxsPos, currHistory ) = que.popleft( )
        remembered.add( frozenset(currBxsPos) )

        for ( newBoxes, movedBox, direction ) in genAllPossibleNewBoxesPositions( currBxsPos, board ):
            if all( [ ( x in targets ) for (syf, x) in newBoxes ] ):
                print( currHistory + [( movedBox, direction )] )
                validation = validateMoves( startPosition, boxesStart, currHistory + [( movedBox, direction )], board )
                if( validation != False ):
                    return validation

            if( newBoxes not in remembered ):
                que.append(  ( frozenset(newBoxes), currHistory + [( movedBox, direction )] ) )

def addUniqueness( boxes ):
    i = 0
    ret = set()
    for el in boxes:
        ret.add( ( i, el ) )
        i += 1
    return ret

def closestDistanceBFS( storageman, goal, board, boxes ):
    visited = set()
    que = deque()
    que.append( ( storageman, '' ) )
    if storageman == goal:
        return ''

    while len( que ) > 0:
        ( currPos, history ) = que.popleft()
        visited.add( currPos )

        for i in range( 4 ):
            ( rDiff, cDiff ) = directions[i]
            newPos = ( currPos[0] + rDiff, currPos[1] + cDiff )
            if( newPos == goal ):
                return history + strDirections[i]

            elif (( board[ newPos[0] ][ newPos[1] ] != 'W' ) and
                  ( newPos not in boxes ) and
                  ( newPos not in visited ) ):
                que.append( ( newPos, history + strDirections[i] ) )
    return False

def validateMoves( storageman, boxess, moves, board ):
    boxes = { x for x in boxess }
    storagemanMoves = ''
    for ( (bR, bC), direction ) in moves:
        ( rDiff, cDiff ) = directions[ direction ]
        res = closestDistanceBFS( storageman, ( bR - rDiff, bC - cDiff ), board, boxes )
        if( res == False ):
            return False
        
        storagemanMoves += res + strDirections[direction]
        storageman = ( storageman[0] + rDiff, storageman[1] + cDiff )
        boxes.remove( ( bR, bC ) )
        boxes.add( ( bR + rDiff, bC + cDiff ) )
    return storagemanMoves

def calcDist( a, b ):
    return abs(a[0] - b[0]) + abs(a[1] + b[1])

def zad3():
    with open( 'zad_output.txt', 'w' ) as out:
        with open( 'zad_input.txt' ) as inp:
            rows = []
            for line in inp:
                rows.append( line.strip('\n') )

            sokoban = findStorageman( rows )
            boxes = findBoxes( rows )
            targets = findAllTargets( rows )
            
            print( sokobanButBy( sokoban, boxes, targets, rows ) )
            print(  )

if __name__ == '__main__':
    zad3()

#trzeba jakoś rozróżniać konkretne skrzynki
#czyli funkcja która odpowiada za generowanie nowych stanów musi sprawdzić która skrzynka została ruszona i wysłać to do BFS
#ten ogarnie czy taka kombinacja stanów już była w grze i wtedy podejmie decyzję czy ją dodać
