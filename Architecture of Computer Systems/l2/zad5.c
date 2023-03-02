#include <stdio.h>
#include <stdint.h>

int32_t threefourths( int32_t x ){
    int32_t pom = x >> 2; //dzielenie całkowite
    int32_t r = x & 3; //reszta z dzielenia przez 4
    pom = pom + ( pom << 1 ); // pom *= 3
    r = r + ( r << 1 ); //r *= 3
    return pom + ( r >> 2 );
}

int main(){
    printf( "%d \n", threefourths( 6 ) );
    printf( "%d \n", threefourths( 1541 ) );
    printf( "%d \n", threefourths( 6843278 ) );
}