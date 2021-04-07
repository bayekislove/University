#include<iostream>
#include<complex>

#define EM 0.5772156649

using namespace std;

template<typename T>
complex<T> calculate_gamma(complex<T> z, int it_num)
{
    complex<T> calcResult = 1;
    for(complex<T> n(1.0, 0.0); n.real() < it_num; n += 1.0)
    {
        calcResult *= pow( (complex<T>(1.0, 0.0) + complex<T>(1.0, 0.0)/n), z) / (complex<T>(1.0, 0.0) + (z / n));
    }

    return calcResult / z;
}

template<typename T>
complex<T> calculate_gamma_B(complex<T> z, int it_num)
{
    complex<T> calcResult = 1;
    for(complex<T> n(1.0, 0.0); n.real() < it_num; n += 1.0)
    {
        calcResult *= (complex<T>(1.0, 0.0) + z / n) * exp( -z/n );
    }
    return z * exp(EM * z) * calcResult;
}

int main()
{
    cout << calculate_gamma(complex<double>(0.0, 1.0), 700) << endl; //okropna zbieżność
    cout << calculate_gamma(complex<double>(3.0, 0.0), 700) << endl;
    cout << calculate_gamma(complex<double>(2.0, 0.0), 700) << endl;
    cout << calculate_gamma(complex<double>(2.0, 3.0), 700) << endl;
    cout << calculate_gamma_B(complex<double>(3.0, 0.0), 700) << endl;
    cout << calculate_gamma_B(complex<double>(2.0, 0.0), 700) << endl;
}