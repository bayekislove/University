def opt_dist( tab, D ):
    if(D == 0): 
        return tab.count('1')

    opt_changes = D
    changed_so_far = 0

    def pom():
        changes = 0 if tab[it] == '1' else 1

        changes += tab.count('0', it + 1, it + D)
        changes += tab.count('1', it + D)

        return changed_so_far + changes

    for it in range( len(tab) - D + 1 ):
        new_ret = pom()
        if new_ret < opt_changes:
            opt_changes = new_ret
        if( tab[it] == '1' ):
            changed_so_far += 1

    return opt_changes

#print( opt_dist([0,1,0,0], 3) )
#print( opt_dist([0,1,1,0,1,0,0], 3) )
#print( opt_dist([0,1,1,1,1,0,0], 3) )
print( opt_dist('0010001000', 5) )
print( opt_dist('0010001000', 4) )
print( opt_dist('0010001000', 3) )
print( opt_dist('0010001000', 2) )
print( opt_dist('0010001000', 1) )
print( opt_dist('0010001000', 0) )