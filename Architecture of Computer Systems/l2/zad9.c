#include <stdio.h>
#include <stdint.h>

//0x55555555 = 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01
//0x33333333 = 0011 0011 0011 0011 0011 0011 0011 0011
//0x0f0f0f0f = 00001111 00001111 00001111 00001111
//0x00ff00ff = 000000001111111 0000000011111111
//0x0000ffff = 0000000000000001111111111111111

uint32_t bits_set(uint32_t x){
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x & 1;
}

int main(){
    printf( "%d \n", bits_set(1) );
    printf( "%d \n", bits_set(3U) );
}