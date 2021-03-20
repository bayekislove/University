words = set()

for line in open('words_for_ai1.txt', encoding='utf-8'):
    words.add(line.strip('\n'))

def pom( inp ):
    calculated = dict()

    def find_opt_division( inp ):
        if( inp == '' ):
            return ('', 0)
        starters = list()
        helper = ''
        for i in range( len( inp ) ):
            helper += inp[i]
            if helper in words:
                if( inp[ (i+1): ]) in calculated: #we now how divide remaining string in the best way
                    pom_string = calculated.get( inp[ (i+1): ])[0] 
                    pom_result = calculated.get( inp[ (i+1): ])[1]
                else:
                    pom = find_opt_division( inp[ (i+1): ] )
                    if(pom == None):
                        continue
                    pom_string = pom[0]
                    pom_result = pom[1]
                starters.append( (helper, pom_string, len(helper)**2 +  pom_result) )
        if( starters == [] ):
            return None
        best_pair = ('', '', 0)
        for guess in starters:
            if( guess[2] > best_pair[2] ):
                best_pair = guess
        calc_string = best_pair[0] + ( ' ' if best_pair[1] != '' else '' ) + best_pair[1]
        calculated[inp] = ( calc_string, best_pair[2] )
        return ( calc_string, best_pair[2] )

    return find_opt_division(inp)[0]

def tadeusz():
    with open('zad2_output.txt', 'ab' ) as out_file:
        for line in open( 'zad2_input.txt', encoding='utf-8' ):
            out_file.write( ( pom( line.strip('\n') ) ).encode('UTF-8') )
            out_file.write( '\n'.encode('UTF-8') )

tadeusz()

stop = time.time()
print( stop - start )