#include<iostream>
#include<vector>
#include<iterator>
#include<fstream>
#include<numeric>

using namespace std;

int nwd(int a, int b)  
{  
    if (a == 0)  
        return b;  
    return nwd(b % a, a);  
}  
  
int euler(unsigned int n)  
{  
    unsigned int result = 1;  
    for (unsigned int i = 2; i < n; i++)  
        if ( gcd(i, n) == 1 )  
            result++;  
    return result;  
} 

void zapisz(unsigned int k){
    vector<unsigned int> V;
    ofstream file("phi.txt");
    ostream_iterator<unsigned int> inp(file, ";");

    for(unsigned int i = 1; i <= k; i++)
    {
        V.push_back( euler(i) );
    }

    copy( V.begin(), V.end(), inp );
    
}

int main()
{
    zapisz(3);
}