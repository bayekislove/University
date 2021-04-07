#include<iostream>
#include<ratio>
#include<limits>
using namespace std;

template<int N>
auto harm() {
    if constexpr (N == 1) {
       return std::ratio<1,1>();   
    } else {
       return std::ratio_add< decltype(harm<N-1>()), std::ratio<1,N> >();
    }
}

int main(){
    cout << decltype(harm<46>())::num << " " << decltype(harm<46>())::den << endl;
}