from math import ceil

def calc2( a, b ):
    res = []
    while ( a != 0 ):
        res.append( ceil( b / a ) )
        print( a )
        c = a
        a = -b % a
        b *= ceil( b / c )
    return res

print( calc2( 4, 17 ) )