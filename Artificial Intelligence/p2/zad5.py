from  heapq  import heappop, heappush

def moveBoard( direction, positions, board ):
    ( rDiff, cDiff ) = commandoDirections[direction]
    newPos = set()
    for (r, c) in positions:
        newPos.add( (r + rDiff, c+cDiff) if board[r + rDiff][c+cDiff] != '#' else (r, c) )
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

rememberedClosestDistance = dict()

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

def aStarCommando( positions, vents, h, board ):
    #struktura danych -> ( koszt_dla_wcześniejszych węzłów, pozycje_komandosów, historia_ruchów )
    heap = []
    visited = set()
    visited.add(  tuple(positions) )
    heappush( heap, ( h(positions, vents, board), positions, '' ) )

    while( len(heap) > 0 ):
        ( currCostA, currCommando, moveHistory ) = heappop( heap )
        visited.add( tuple(currCommando) )

        for i in range( 4 ):
            newPos = moveBoard( i, currCommando, board )

            if( tuple(newPos) in visited ):
                continue
            
            for x in newPos:
                flague = x in vents
                if( not flague ):
                    break
            if( flague ):
                return moveHistory + commandoStrDirections[i]

            else:
                currCost = h( newPos, vents, board )
                heappush( heap, ( currCost + len(moveHistory), newPos, moveHistory + commandoStrDirections[i] ) )

commandoDirections = [ (1, 0), (0, -1), (-1, 0), (0, 1) ] # [down, left, up, right]
commandoStrDirections = ['D', 'L', 'U', 'R']

def zad5():
    with open( 'zad_output.txt', 'w' ) as out:
        with open( 'zad_input.txt' ) as inp:
            rows = []
            for line in inp:
                rows.append( line.strip('\n') )

            sPos = startPositions( rows )
            endPos = vents( rows )

            res = aStarCommando( sPos, endPos, closestDistanceAll, rows )
            out.write( res )

if __name__ == '__main__':
    zad5()