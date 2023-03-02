#include <stdio.h>
#include <stdint.h>

uint32_t a(uint32_t x, unsigned int k)
{
    return x << k;
}

uint32_t b(uint32_t x, unsigned int k)
{
    return x >> k;
}

int main()
{
    printf(  "%u \n", a(3, 2) );
    printf(  "%u \n", b(13, 2) );
}