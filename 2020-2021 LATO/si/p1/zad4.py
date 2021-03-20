def optDist( tab, D ):
    ones = tab.count('1')

    if D == 0:
        return ones
    best = len( tab )

    for i in range( 0, len(tab) - D + 1 ):
        toChange = ones + D - 2 * tab.count('1', i, i + D) 
        if( best > toChange ):
            best = toChange

    return best