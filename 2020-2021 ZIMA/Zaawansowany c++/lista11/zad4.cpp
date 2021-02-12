#include<iostream>

template<size_t N, typename T = double>
struct Inner
{
    static T dot(T *a, T *b)
    {
        return (*a) * (*b) + Inner<N-1, T>::dot( (++a), (++b) );
    };
};

template<typename T>
struct Inner<1, T>
{
    static T dot(T *a, T *b)
    {
        return (*a) * (*b);
    };
};

template<size_t N, typename T = double> T inner(T *a, T *b)
{
    return Inner<N, T>::dot(a, b);
}

int main()
{
    double a[3] = {1, 2, 3};
    double b[3] = {1, 2, 3};
    int prod = inner<3>(a, b);
    std::cout << prod << std::endl;
}