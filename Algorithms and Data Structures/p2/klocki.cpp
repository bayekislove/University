#include <iostream>
#include <stdio.h>
#include <stdint.h>

using namespace std;

void func( int* arr, int size, int sum ){
    //mamy mapa w którym trzymamy pary {klucz, wartość}, gdzie klucz to różnica w wysokościach a wartość to wysokość najw wieży
    //tak de facto trzymamy tutaj tylko takie pary, które nam się przydadzą, bo wysokości niższych wieży niż najwyższa
    //danych wysokości będą zastąpialne przez różnicę najwyższej wieży (jak jest więcej niż więcej pasujących wież danej 
    //wysokości no to bez różnicy którą wybierzemy, więc możemy wybrać najwyższą) a najwyższa przydaje się do ustawienia
    //najwyższych wieży równej długości
    int* towers = new int[sum];
    for( int i = 0; i < sum; i++){
        towers[i] = -1;
    }

    towers[0] = 0;
    int max_calculated = 0;
    int* new_tab;
    for( int i = 0; i < size; i++ )
    {
        int new_max_calc = max_calculated;
        new_tab = new int[sum];

        for( int i = 0; i < sum; i++){
            new_tab[i] = -1;    
        }
        
        for( int j = 0; j < max_calculated + 1; j++ ){
            if( towers[j] == -1 )
                continue;
            new_tab[ j ] = max( towers[j], new_tab[j] );

            new_tab[ j + arr[i] ] = max( towers[j] + arr[i], new_tab[ j + arr[i] ] );
            new_max_calc = max( j + arr[i], new_max_calc );

            //wysokość niższej na starcie wieży -> od wysokości większej od róznicy odejmujemy roznice dod klocek
            int new_tower_max_height = max( towers[j] - j + arr[i], towers[j] ); //nowa maksymalna wysokosc
            int new_diff = abs( arr[i] - j );
            new_tab[ new_diff ] = max( new_tab[ new_diff ], new_tower_max_height ); 
            //wysokosc najwyzszej wiezy
        }
        max_calculated = new_max_calc;
        delete[] towers;
        towers = new_tab;
    }
    if( towers[0] != 0 && towers[0] != -1 ){
        printf( "TAK\n%d\n", towers[0] );
        delete[] towers;
        return;
    }
    for(int i = 1; i < sum; i++){
        if( towers[i] != i && towers[i] != -1 && towers[i] != 0 ){
            printf( "NIE\n%d\n", i );
            delete[] towers;
            return;
        }
    }
}

int main(){
    int32_t how_many;
    scanf( "%d", &how_many );

    int bricks[how_many];
    for( int32_t i = 0; i < how_many; i++ ){
        scanf( "%d", &bricks[i] );
    }
    int sum = 0;
    for( int i = 0; i < how_many; i++ ){
        sum += bricks[i];
    }

    func( bricks, how_many, sum );
}