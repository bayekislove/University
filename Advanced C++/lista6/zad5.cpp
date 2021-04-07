#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

void perm(string inp)
{
    sort(inp.begin(), inp.end());
    do{
        cout << inp << endl;
    }while(next_permutation(inp.begin(), inp.end()));
}

int main()
{
    string test = "test"; 
   perm(test);
}