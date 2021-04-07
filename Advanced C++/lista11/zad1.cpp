#include<iostream>

template<int N> struct Lucas
{
    static constexpr int val = Lucas<N-1>::val + Lucas<N-2>::val;

    public:
    constexpr int operator()()
    {
        return this->val;
    }
};

template<> struct Lucas<1>
{
    static constexpr int val = 1;

    public:
        constexpr int operator()() { return 1; }
};

template<> struct Lucas<0>
{
    static constexpr int val = 2;

    public:
        constexpr int operator()() { return 2; }
};

int main()
{
    constexpr auto l3 = Lucas<3>()();
    std::cout << l3 << std::endl;
}