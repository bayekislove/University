from random       import randint
from collections  import deque

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

def visualize( moves, viss ):
    vis = [ r[:] for r in viss ]
    for (cR, cC) in moves:
        vis[cR][cC] = 'S' 
    ret = ''
    for a in vis:
        ret += ''.join( a ) + '\n'
    print( ret )

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

def makeMoves( positions, board ):
    blankBoard = prepareToVisualize( board )
    lastMove = -1
    moves = []  
    while( len( positions ) > 2 ):
        if( len( positions ) > -1 ):
            direction = randint( 0, 3 ) #0 down, 1 left, 2 up, 3 right
            while( direction == makeMoves.opposite[ lastMove ] ):
                direction = randint( 0, 3 )
            moves.append( makeMoves.strDirections[ direction ] )
            lastMove = direction
            positions = moveBoard( direction, positions, board )
            #print( visualize( positions, blankBoard ) )
        
        #else:
        #    guesses = [ len( moveBoard( i, positions, board ) ) for i in range( 4 ) ]
            #print( min( guesses ) )
        #    dirr = guesses.index( min( guesses ) )
        #    positions = moveBoard( dirr, positions, board )
        #    moves.append( makeMoves.strDirections[ dirr ] )
    return (positions, ''.join( moves ) )

def commandoBFS( positions, board, moves, vents ):
    bfs = deque()
    bfs.append( ( positions, moves ) )
    remembered = set()
    remembered.add( (tuple(positions)) )
    while( len( bfs ) > 0 ):
        ( currPos, currHis ) = bfs.pop()
        remembered.add( (tuple(currPos)) )
        for i in range( 4 ):
            newPos = set()
            ( rD, cD ) = commandoBFS.directions[i]
            for (r, c) in currPos:
                if( board[r + rD][c + cD] == '#' ):
                    newPos.add( (r, c) )
                else:
                    newPos.add( ( r + rD, c + cD ) )
            if ( tuple(newPos) in remembered):
                continue
            flague = True
            for x in newPos:
                flague = x in vents
                if( not flague ):
                    break
            if( flague ):
                return currHis + commandoBFS.strDirections[i]
            else:
                bfs.append( ( newPos, currHis + commandoBFS.strDirections[i] ) )

commandoBFS.directions = [ (1, 0), (0, -1), (-1, 0), (0, 1) ]
moveBoard.directions = [ (1, 0), (0, -1), (-1, 0), (0, 1) ]
commandoBFS.strDirections = ['D', 'L', 'U', 'R']
makeMoves.strDirections = ['D', 'L', 'U', 'R']
makeMoves.opposite = [ 2, 3, 0, 1 ]

def func():
    with open( 'zad_output.txt', 'w' ) as out:
        with open( 'zad_input.txt' ) as inp:
            rows = []
            for line in inp:
                rows.append( line.strip('\n') )
            #print( vents(rows) )
            best_path = 151
            while( best_path > 150 ):
                (path, mvs) = makeMoves( startPositions(rows), rows )
                while( len(mvs) > 110 ):
                    (path, mvs) = makeMoves( startPositions(rows), rows )
                #print( len(mvs) )
                res = commandoBFS( path, rows, mvs, vents(rows) )
                #print( len(res) )
                if( len(res) <= 150 ):
                    #visualize( path, prepareToVisualize(rows) )
                    #print( mvs )
                    #print( res )
                    out.write( res )
                    return

func()