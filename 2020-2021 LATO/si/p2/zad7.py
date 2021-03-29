from  random       import randint
from  collections  import deque
from  heapq        import heappop, heappush

def prepareToVisualize( board ):
    ret = []
    for row in board:
        r = []
        for position in row:
            r.append( position if position in {"#", "B", "G"} else ' ' )
        ret.append( r )
    return ret

def moveBoard1( direction, positions, board ):
    ( rDiff, cDiff ) = moveBoard1.directions[direction]
    newPos = set()
    for (row, pos) in positions:
        if( board[ row ][ pos ] not in { 'S', 'B' } ):
            continue
        newPos.add( (row, pos) if board[row+rDiff][pos+cDiff] == '#' else (row+rDiff, pos+cDiff) )
    return newPos

def moveBoard2( direction, positions, board ):
    ( rDiff, cDiff ) = commandoDirections[direction]
    newPos = set()
    for (r, c) in positions:
        newPos.add( (r + rDiff, c+cDiff) if board[r + rDiff][c+cDiff] != '#' else (r, c) )
    return newPos

def startPositions( board ):
    ret = set()
    for j in range( len(board) ):
        for i in range( len( board[j] ) ):
            if board[j][i] in {'S', 'B'}:
                ret.add( (j, i) )
    return ret

def vents( board ):
    ret = set()
    for j in range( len(board) ):
        for i in range( len( board[j] ) ):
            if board[j][i] in {'G', 'B' }:
                ret.add( (j, i) )
    return ret

def closestDistanceBFS( position, vents, board ):
    if( position in rememberedClosestDistance ):
        return rememberedClosestDistance[position]

    if( position in vents ):
        return 0
    visited = set()
    a = set()
    a.add( position )
    it = 0
    while( True ):
        new_set = set()
        for (r, c) in a:
            for i in range( 4 ):
                ( rD, cD ) = commandoDirections[i]
                newRow = r + rD
                newCol = c + cD
                if( (newRow, newCol) in vents ):
                    rememberedClosestDistance[position] = it + 1
                    return it + 1
                else:
                    new_set.add( (newRow, newCol) if board[newRow][newCol] != '#' else (r, c) )
        a = new_set
        it += 1

def closestDistance( position, vents, board ):
    return min( [ abs(position[0] - vent[0]) + abs(position[1] - vent[1]) for vent in vents ] )

def closestDistanceAll( positions, vents, board ):
    return max( [ closestDistanceBFS( position, vents, board ) for position in positions ] )

def aStarCommando( positions, vents, h, board, sN ):
    #struktura danych -> ( koszt_dla_wcześniejszych węzłów, pozycje_komandosów, historia_ruchów )
    heap = []
    visited = set()
    visited.add(  tuple(positions) )
    heappush( heap, ( h(positions, vents, board), positions, '' ) )

    while( len(heap) > 0 ):
        ( currCostA, currCommando, moveHistory ) = heappop( heap )
        visited.add( tuple(currCommando) )

        for i in range( 4 ):
            newPos = moveBoard2( i, currCommando, board )

            if( tuple(newPos) in visited ):
                continue
            
            for x in newPos:
                flague = x in vents
                if( not flague ):
                    break
            if( flague ):
                return moveHistory + commandoStrDirections[i]

            else:
                currCost = ( (1+sN) * h( newPos, vents, board ) ) + len(moveHistory)
                heappush( heap, ( currCost, newPos, moveHistory + commandoStrDirections[i] ) )

def makeMoves( positions, board, num ):
    blankBoard = prepareToVisualize( board )
    lastMove = -1
    moves = []  
    while( len( positions ) > 10 ):
        if( len( positions ) > -1 ):

            direction = randint( 0, 3 ) #0 down, 1 left, 2 up, 3 right
            while( direction == makeMoves.opposite[ lastMove ] ):
                direction = randint( 0, 3 )
            moves.append( makeMoves.strDirections[ direction ] )
            lastMove = direction
            positions = moveBoard1( direction, positions, board )

    return (positions, ''.join( moves ) )

commandoDirections = [ (1, 0), (0, -1), (-1, 0), (0, 1) ] # [down, left, up, right]
commandoStrDirections = ['D', 'L', 'U', 'R']
makeMoves.strDirections = ['D', 'L', 'U', 'R']
makeMoves.opposite = [ 2, 3, 0, 1 ]
moveBoard1.directions = [ (1, 0), (0, -1), (-1, 0), (0, 1) ]
rememberedClosestDistance = dict()

def zad7():
    with open( 'zad_output.txt', 'w' ) as out:
        with open( 'zad_input.txt' ) as inp:
            rows = []
            for line in inp:
                rows.append( line.strip('\n') )

            ends = vents(rows)
            best_path = 151
            while( best_path > 80 ):
                (path, mvs) = makeMoves( startPositions(rows), rows, 2 )
                best_path = len(mvs)
            res = aStarCommando( path, ends, closestDistanceAll, rows, 0.25 )
            out.write( mvs + res )

zad7()
                