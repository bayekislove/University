//Kacper Bajkiewicz
//314438
//KPO

#include <stdio.h>

void multiples( long long int a, long long int b, long long int num )
{
    a += ( a % num ) == 0 ? 0 : ( num - a % num );
    while( a <= b ){
        printf( "%lld ", a );
        a += num;
    };
    printf( "\n" );
}

int main()
{
    long long int a, b;
    scanf( "%lld %lld", &a, &b );
    multiples( a, b, 2021 );
}