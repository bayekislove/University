import heapq

def moveBoard( direction, positions, board ):
    ( rDiff, cDiff ) = moveBoard.directions[direction]
    newPos = set()
    for (row, pos) in positions:
        if( board[ row ][ pos ] not in { 'S', 'B' } ):
            continue
        newPos.add( (row, pos) if board[row+rDiff][pos+cDiff] == '#' else (row+rDiff, pos+cDiff) )
    return newPos

def prepareToVisualize( board ):
    ret = []
    for row in board:
        r = []
        for position in row:
            r.append( position if position in {"#", "B", "G"} else ' ' )
        ret.append( r )
    return ret

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

def closestDistance( position, vents ):
    return min( [ abs(position[0] - vent[0]) + abs(position[1] - vent[1]) for vent in vents ] )

def closestDistanceAll( positions ):
    return min( [ closestDistance( [] ) ] )

def aStar( positions, vents, h ):
    #struktura danych -> ( koszt_dla_wcześniejszych węzłów, pozycje_komandosów )
    heap = []
    visited = set()
    
    while( len(heap) > 0 ):
        ( curr heapq.heappop( heap )

print( closestDistance( (1, 1), [(3, 4), (1, 1)] ) )