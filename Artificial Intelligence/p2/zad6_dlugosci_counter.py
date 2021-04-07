with open( 'zad6_dlugosci.txt' ) as dlugosci:
    tab = []
    for line in dlugosci:
        tab = line.split( ';' )
    print( sum( map( lambda x: int(x), tab[:-1] ) ) )