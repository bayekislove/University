#include <stdio.h>
#include <stdint.h>

uint32_t if_power_of_two(uint32_t x)
{
    return x & (x - 1);
}

int main()
{
    printf( "%u \n", if_power_of_two(7) );
    printf( "%u \n", if_power_of_two(4) );
}