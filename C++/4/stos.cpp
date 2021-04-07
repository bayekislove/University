#include "stos.hpp"
using namespace std;

stos::stos(int poj){
    if(poj > 100){
        throw invalid_argument("Proszę podać liczbę mniejszą od 100!\n");
    }
    else{
        pojemnosc = poj;
        ile = 0;
        tablica = new string[poj];
    }
}

stos::stos(): stos(1) {}; //konstruktor deleg. i bezparam.

stos::stos(stos& inp){
    pojemnosc = inp.getpoj();
    ile = inp.rozmiar();
    tablica = new string[pojemnosc];
    for(int i{0}; i < inp.ile; i++){
        tablica[i] = inp.tablica[i];
    }
}

stos::stos(stos&& inp):
    pojemnosc(inp.pojemnosc),
    ile(inp.ile),
    tablica(inp.tablica) {
    inp.tablica = nullptr;
    inp.ile = 0; inp.pojemnosc = 0;
    }

stos::stos(initializer_list<string> lista){
    if(lista.size() == 0){
        throw out_of_range("Insert non-empty list!");
    }
    tablica = new string[lista.size()];
    ile = 0;
    pojemnosc = 100;
    for(initializer_list<string>::iterator it = lista.begin(); it < lista.end(); it++){
        tablica[ile] = *it;
        ile++;
    }
}

stos & stos::operator= (stos& inp){
    cout << "Kopiujace!" << '\n';
    pojemnosc = inp.getpoj();
    ile = inp.rozmiar();
    tablica = new string[pojemnosc];
    for(int i{0}; i < inp.ile; i++){
        tablica[i] = inp.tablica[i];
    }
}

stos && stos::operator= (stos&& inp){
    cout << "Przenoszace!" << '\n';
    this->pojemnosc = inp.pojemnosc;
    this->ile = inp.rozmiar();
    this->tablica = inp.tablica;
    inp.tablica = nullptr;
    inp.ile = 0; inp.pojemnosc = 0;
}

void stos::wloz(string inp){
    if(ile == pojemnosc - 1){
        throw invalid_argument("Stos overflow!");
    }
    tablica[ile] = inp;
    ile++;
}

stos stos::odwroc(){
    stos zwrot(pojemnosc);
    for(int i{0}; i < ile; i++){
        zwrot.wloz(tablica[i]);
    }
    return zwrot;
}

string stos::sprawdz(){
    return tablica[ile-1];
}

string stos::zdejmij(){
    ile--;
    string pom = tablica[ile];
    tablica[ile] = "";
    return pom;
}

stos::~stos(){
    delete[] tablica;
    ile = 0;
    pojemnosc = 0;
}

int stos::rozmiar(){
    return ile;
}

int stos::getpoj(){
    return pojemnosc;
}