#include<iostream>
#include<random>
using namespace std;

random_device gen;

//algorithm Fishera-Yatesa
template<typename T, int k>
void permutation(T(&inp)[k])
{  
    int size = sizeof(inp)/sizeof(inp[0]);
    for(int i = size - 1; i > 0; i--)
    {
        uniform_int_distribution<int> distribution(0, i);
        int guess = distribution(gen);

        swap(inp[guess], inp[i]);
    }
}

int main()
{
    int foo[5]{0, 1, 2, 3, 4};
    for(int k = 0; k < 10; k++)
    {
        permutation(foo);
        for(int i = 0; i < 5; i++)
        {
        cout << foo[i] << " ";
        }
    cout << endl;
    }
}
