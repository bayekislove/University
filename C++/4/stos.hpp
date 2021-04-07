#include <iostream>
#include <string>
using namespace std;

class stos {
    private:
        int pojemnosc; //max l el
        int ile; //l el
        string *tablica;
    public:
        stos(int poj);
        stos();
        stos(stos& inp);
        stos(stos&& inp);
        stos(initializer_list<string> lista);
        stos odwroc();
        string sprawdz();
        string zdejmij();
        void wloz(string s);
        int rozmiar();
        int getpoj();
        stos & operator= (stos&);
        stos & operator= (stos&&);
        ~stos();
};