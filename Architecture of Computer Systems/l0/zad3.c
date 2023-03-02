#include <stdio.h>
#include <stdint.h>

uint32_t douse(uint32_t x, int k)
{
    return x & ( ~( 1 << ( k - 1 ) ) );
}

uint32_t set(uint32_t x, int k)
{
    return x | ( 1 << (k - 1) );
}

uint32_t neg(uint32_t x, int k)
{
    return x ^ ( 1 << ( k - 1 ) );
}

int main()
{
    printf( "%u \n", douse( 17, 1 ) );
    printf( "%u \n", set( 16, 1 ) );
    printf( "%u \n", neg( 16, 1 ) );
    printf( "%u \n", neg( 17, 1 ) );
}