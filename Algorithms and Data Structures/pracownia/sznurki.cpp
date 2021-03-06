#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long bin_search_inc( vector< pair<long, long>>& vect, long val, long val_to_inc, long start )
{
    long mid;
    long end = vect.size() - 1;
    while( end > start )
    {
        mid = (end + start)/ 2 + ( (end + start) % 2 != 0); //ceil
        if( vect[ mid ].first > val )
        {
            end = mid - 1; 
        }
        else
        {
            start = mid;
        }
    }
    if( vect[start].first == val )
    {
        vect[start].second += val_to_inc;
        return start;
    }
    return 0;
}

long find( vector< pair<long, long> >& vect )
{
    sort( vect.begin(), vect.end() );

    long ret = 0;
    for( unsigned long it = 0; it < vect.size(); it++ )
    {
        if( vect[it].second % 2 == 1 )
        {
            vect[it].second -= 1;
            it--;
            ret++;
        }
        else //vect[it].second % 2 == 0
        {
            vect[it].first = vect[it].first * 2;
            vect[it].second = vect[it].second / 2;
            if( vect[it].second == 0 ){
                continue;
            }
            if( bin_search_inc( vect, vect[it].first, vect[it].second, it + 1 ) == 0 )
            { 
                it--; 
            }
        }
    }
    return ret;   
}

int main()
{
    long how_many;
    scanf( "%ld", &how_many );
    long num, quantity;
    vector<pair<long int, long int>> nums;  

    for( int i = 0; i < how_many; i++ )
    {
        scanf( "%ld %ld", &num, &quantity );
        nums.push_back( make_pair( num, quantity ) );
    }
    printf( "%ld \n", find( nums ) );
    // vector<pair<long int, long int>> myVec = { {-1, -1}, {2, 5}, {3, 10} };
    // cout << bin_search_inc( myVec, 3, 1) << endl;
    // cout << myVec[2].second << endl;
}