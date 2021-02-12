#include<iostream>

template<int N> struct Fact
{
    static constexpr int val = N * Fact<N-1>::val;

    public:
        constexpr int operator()() { return this.val; };
};

template<> struct Fact<1> 
{ 
    static constexpr int val = 1;

    public:
        constexpr int operator()() { return 1; }
};

template<> struct Fact<0> 
{ 
    static constexpr int val = 1;

    public:
        constexpr int operator()() { return 1; }
};

template<int N, int K> struct Bin_Coeff
{
    static constexpr int val = Fact<N>::val / (Fact<K>::val * Fact<N-K>::val);

    public:
        constexpr int operator()() { return this->val; };
};

int main()
{
    constexpr int bcoeff = Bin_Coeff<3, 2>()();
    std::cout << bcoeff << std::endl;
}