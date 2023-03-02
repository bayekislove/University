#include <stdio.h>
#include <stdint.h>

int main(){
    int32_t x = INT32_MIN + 713;
    int32_t y = INT32_MIN + 5;
    int32_t z = INT32_MIN;
    double dx = (double)x;
    double dy = (double)y;
    double dz = (double)z;

    printf( "%d \n", (dx * dy) * dz == dx * ( dy * dz ) );
    printf( "%d \n", dx - dy == (double)(x - y) );
    printf( "%d \n", (1.0 / 1.0 == 0.0 / 0.0) );
}