#include<iostream>

template<int A, int B> struct GCD
{
    static constexpr int val = GCD<B, A%B>::val;

    public: 
        constexpr int operator()() { return this->val; };
};

template<int A> struct GCD<A, 0>
{
    static constexpr int val = A;

    public: 
        constexpr int operator()() { return A; };
};

int main()
{
    constexpr auto g = GCD<4,8>()();
    std::cout << g << std::endl;
}