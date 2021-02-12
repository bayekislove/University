#include<iostream>
#include<fstream>
#include<random>
using namespace std;

random_device gen;

void uni()
{
    uniform_real_distribution<double> distribution(-200000.0, 200000.0);
    ofstream to_file;
    to_file.open("uni.csv");
    for(int i = 0; i < 1000; i++)
    {
        cout << i << endl;
        to_file << distribution(gen) << ',';
    }
    to_file.close();
    cout << endl;
}

void bin()
{
    binomial_distribution<int> distribution(INT32_MAX - 1, 0.5);
    ofstream to_file;
    to_file.open("bin.csv");
    for(int i = 0; i < 1000; i++)
        to_file << distribution(gen) - 1073741823 << ',';

    to_file.close();
    cout << endl;
}

void nor()
{
    normal_distribution<double> distribution(0.0, 1.0);
    ofstream to_file;
    to_file.open("nor.csv");
    for(int i = 0; i < 1000; i++)
        to_file << distribution(gen) << ',';

    to_file.close();
    cout << endl;
}

int main()
{
    uni();
    bin();
    nor();
}