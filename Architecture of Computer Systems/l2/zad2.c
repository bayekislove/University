#include <stdio.h>
#include <stdint.h>
#include <limits.h>

void swap(int32_t x, int32_t y ){
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
    printf( "X-> %d Y-> %d \n", x, y );
}

int main(){
    swap( 7, 100 );
}