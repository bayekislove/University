#include "tab_bit.hpp"

int main()
{
    tab_bit t(46); // tablica 46-bitowa (zainicjalizowana zerami)
    tab_bit u(45ull); // tablica 64-bitowa (sizeof(uint64_t)*8)
    tab_bit v(t); // tablica 46-bitowa (skopiowana z t)
    tab_bit w(tab_bit{1, 0, 1, 1, 0, 0, 0, 1}); // tablica 8-bitowa (przeniesiona)
    v[0] = 1; // ustawienie bitu 0-go bitu na 1
    t[45] = true; // ustawienie bitu 45-go bitu na 1
    u[45] = u[46] = u[63]; // przepisanie bitu 63-go do bitow 45-go i 46-go
    cout<<"Test z zadania:" << t <<endl; // wysietlenie zawartości tablicy bitów na ekranie
    cout << "tablica w: " << w << endl << endl;
    cout <<"Moje osobiste testy:" << endl << endl;;
    tab_bit pom1(3);
    cout <<"pom1 to: " << pom1<< endl;
    cout <<"!pom1 to: " << !pom1 << endl;
    cout <<"pom1 | !pom1 to: " << (pom1 | !pom1) << endl;
    cout <<"pom1 & !pom1 to: " << (pom1 & !pom1) << endl;
    cout <<"pom1 ^ !pom1 to: " << (pom1 & !pom1) << endl;
    cout << "pom1 |= !pom1";
    pom1 |= !pom1;
    cout << "pom1 to teraz: " << pom1 << endl; 
    tab_bit pom2(tab_bit(4));
    pom2[2] = 1;
    cout << "pom2 to nowa tablica, wyglada tak: " << pom2 << endl;
    cout << "a pom1 | pom2 tak: " << (pom1 | pom2) << endl;
    }