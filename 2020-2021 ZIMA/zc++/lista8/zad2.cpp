#include<iostream>
#include<complex>
#include<fstream>

using namespace std;

template<typename T>
complex<T> calculate_dzeta(complex<T> z, int num_it)
{
    complex<T> res(0.0, 0.0);
    for(int n = 1; n < num_it; n++)
    {
        res += (n % 2 == 0 ? -1.0 : 1.0) / (pow(complex<T>(n, 0.0), z)); // n%2
    }

    return 1.0 / (1.0 - pow(2.0, complex<T>(1.0, 0.0) - z)) * res;
}

int main()
{
    double re[501];
    double im[501];
    for(uint i = 0; i <= 500; i ++)
    {
        complex<double> pom = calculate_dzeta(complex<double>(0.5, -25.0 + i * 0.1), 20000);
        re[i] = pom.real();
        im[i] = pom.imag();
    }

    ofstream toFile;
    toFile.open("riemanncsv.csv");
    for(uint i = 0; i <= 500; i++)
    {
        toFile << re[i] << ',';
    }
    toFile << endl;
    for(uint i = 0; i <= 500; i++)
    {
        toFile << im[i] << ',';
    }
    toFile << endl;
}