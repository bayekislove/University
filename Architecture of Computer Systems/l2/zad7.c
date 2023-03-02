#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define N 32

int32_t abs(int32_t x ){
    return ( x ^ x >> (N - 1) ) - x >> (N - 1);
}

int main(){
    printf( "%d \n", abs( -5 ) );
    printf( "%d \n", abs( 0 ) );
    printf( "%d \n", abs( 5 ) );
}