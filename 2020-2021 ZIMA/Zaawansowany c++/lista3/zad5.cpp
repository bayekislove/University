#include<iostream>
#include<random>
#include<chrono>

using namespace std;

//std::random_device rand_dev;
std::default_random_engine re;//(rand_dev);

struct Matrix{
    double *tab;
    int N;
    Matrix(const int N) : tab(new double[N*N]) { this->N = N; };

    double* operator[](const int i) {return tab + N*i;};

    void operator=(Matrix m1){
        tab = m1.tab;
        N = m1.N;
    }
};

double rand_d(double bot, double top)
{
    return std::uniform_real_distribution<double>(bot, top)(re);
}

Matrix random_matrix(int size)
{
    Matrix m(size);

    for(int i = 0; i < size; i++)
    {
        for(int j{0}; j < size; j++)
        {
            m[i][j] = rand_d(0.5, 2.0);
            
        }
    }
    return m;
}

Matrix przemnoz_macierz(int size, Matrix m1, Matrix m2)
{
    Matrix m(size);

    for(int i{0}; i < size; i++)
    {
        for(int j{0}; j < size; j++)
        {
            for(int k{0}; k < size; k++)
            {
                m[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return m;
}

int main(){
    // double **array = new double*[2];
    // for(int i = 0; i < 2; i++)
    //     array[i] = new double[2];
    // array[0][0] = 1.0; array[0][1] = 2.0, array[1][0] = 3.0, array[1][1] = 4.0;
    // double **array2 = new double*[2];
    // for(int i = 0; i < 2; i++)
    //     array2[i] = new double[2];
    // array2[0][0] = 30.0; array2[0][1] = 32.0, array2[1][0] = 60.0, array2[1][1] = 65.0;
    // cout << przemnoz_macierz(2, array, array2)[0][0] << endl;
    Matrix macierz(100);
    auto start = chrono::high_resolution_clock::now();
    for(int i{0}; i < 100; i++)
    {
        macierz = random_matrix(100);
        przemnoz_macierz(100, macierz, macierz);
    }
    auto koniec = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = koniec - start;
    cout << diff.count() / 100 << endl;

    Matrix macierz2(1000);
    start = chrono::high_resolution_clock::now();
    for(int i{0}; i < 2; i++)
    {
        macierz2 = random_matrix(1000);
        przemnoz_macierz(1000, macierz2, macierz2);
    }
    koniec = chrono::high_resolution_clock::now();
    diff = koniec - start;
    cout << diff.count() / 2 << endl;

    start = chrono::high_resolution_clock::now();
    Matrix macierz3 = random_matrix(10000);
    przemnoz_macierz(10000, macierz3, macierz3);
    koniec = chrono::high_resolution_clock::now();
    diff = koniec - start;
    cout << diff.count() << endl;
}