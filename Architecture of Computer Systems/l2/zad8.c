#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define N 32

int32_t sgn(int x ){
    return x >> (N - 1) | -x >> (N - 1) & 1;
}

int main(){
    printf( "%d \n", sgn( INT_MAX ) );
    printf( "%d \n", sgn( 7 ) );
    printf( "%d \n", sgn( 0 ) );
    printf( "%d \n", sgn( INT_MIN ) );
}