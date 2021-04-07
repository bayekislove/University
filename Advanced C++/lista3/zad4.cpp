#include<iostream>
#include<type_traits>
using namespace std;

template<typename T1, typename T2>
void carry(T1 inp1, T2 &inp2)
{
    if constexpr(is_pointer<T1>::value){
        if constexpr (is_convertible<decltype(*inp1), T2>::value){
            inp2 = move(static_cast<T2>(*inp1));
        }
        else{
            throw logic_error("");
        }
    }
    else{
        if constexpr (is_convertible<T1, T2>::value){
            inp2 = move(inp1);
        }
        else{
            throw logic_error("");
        }
    }
}

int main()
{
    int pom = 1;
    double pom2;
    int* pomr = &pom;
    carry(pom, pom2);
    cout << pom2 << endl;
    pom = 2;
    carry(pomr, pom2);
    cout << pom2 << endl;
}