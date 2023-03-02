#include <stdio.h>
#include <stdint.h>

uint32_t copy_bit( uint32_t x, uint32_t i, uint32_t k ){
    uint32_t i_bit = (x >> i) & 1;
    x = x & ~( 1 << k ); //zerujemy k-ty bit
    return x | ( i_bit << k );
}

int main(){
    printf( "%u \n", copy_bit( 22, 4, 0 ) );
    printf( "%u \n", copy_bit( 22, 0, 4 ) );
    printf( "%u \n", copy_bit( 22, 3, 3 ) );
}