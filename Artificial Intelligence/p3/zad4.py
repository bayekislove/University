def B(i,j):
    return 'B_%d_%d' % (i,j)

def writeCorrectSums( rows, cols ):
    for i in range( len(rows) ):
        writeln( 'sum([' + ', '.join( [ B(i, j) for j in range( len(cols) ) ] ) + '], #=, ' + str(rows[i]) + '), ' )
    for j in range( len(cols) ):
        writeln( 'sum([' + ', '.join( [ B(i, j) for i in range( len(rows) ) ] ) + '], #=, ' + str(cols[j]) + '), ' )

def writeRowsLine( rows, colsLen ):
    for i in range( len(rows) ):
        for j in range(1, colsLen - 1):
            writeln( B(i, j) + ' #= 1 #==> ' + B(i, j-1) + ' + ' + B(i, j+1) + ' #>= 1, ' )

def writeColsLine( cols, rowsLen ):
    for j in range( len(cols) ):
        for i in range(1, rowsLen - 1):
            writeln( B(i, j) + ' #= 1 #==> ' + B(i-1, j) + ' + ' + B(i+1, j) + ' #>= 1, ' )

def writeCorrectRectangles( rows, cols ):
    for i in range( len(rows) - 1 ):
        for j in range( len(cols) - 1 ):
            writeln( B(i, j+1) + ' + ' + B(i+1, j) + ' #= 2 #<==> ' + B(i, j) + ' + ' + B(i+1, j+1) + ' #= 2, ' )

def storms(rows, cols, triples):
    writeln(':- use_module(library(clpfd)).')

    rows = list(rows)
    cols = list(cols)

    bs = [ B(i,j) for i in range( len(rows) ) for j in range( len(cols) )]
    
    writeln('solve([' + ', '.join(bs) + ']) :- ')
    writeln('[' + ', '.join(bs) + '] ins 0..1,')

    writeCorrectSums( rows, cols )

    writeCorrectRectangles( rows, cols )

    writeColsLine( cols, len(rows) )
    writeRowsLine( rows, len(cols) )
    
    for i, j, v in triples:
        output.write( '%s #= %d, ' % ( B(i, j), v ) )
    
    writeln('')
    writeln('    labeling([ff], [' +  ', '.join(bs) + ']).' )
    writeln('')
    writeln(":- tell('prolog_result.txt'), solve(X), write(X), nl, told.")

def writeln(s):
    output.write(s + '\n')

if __name__ == '__main__':
    txt = open('zad_input.txt').readlines()
    output = open('zad_output.txt', 'w')

    rows = map(int, txt[0].split())
    cols = map(int, txt[1].split())
    triples = []

    for i in range(2, len(txt)):
        if txt[i].strip():
            triples.append(map(int, txt[i].split()))

    storms(rows, cols, triples)
    output.close()       