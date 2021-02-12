#include"wyrazenie.hpp"
using namespace std;
int main(){
    wyrazenie *jeden = new Dziel(new Mnoz(new Odejm(new zmienna("x"), new liczba(1)), new zmienna("x")), new liczba(2));
    cout << jeden->opis() << endl;
    wyrazenie *dwa = new Dziel(new Dod(new liczba(3), new liczba(5)), new Dod(new liczba(2), new Mnoz(new zmienna("x"), new liczba(7))));
    cout << dwa->opis() << endl;
    wyrazenie *trzy = new Odejm(new Dod(new liczba(2), new Mnoz(new zmienna("x"), new liczba(7))), new Dod(new Mnoz(new zmienna("y"), new liczba(3)), new liczba(5)));
    cout << trzy->opis() << endl;
    wyrazenie *cztery = new Dziel(new Cos(new Mnoz(new Dod(new zmienna("x"), new liczba(1)), new zmienna("x"))), new Pot(new Pot(new e(), new zmienna("x")), new liczba(2)));
    cout << cztery->opis() << endl;
    wyrazenie *w = new Odejm(new pi(),new Dod(new liczba(2),new Mnoz(new zmienna("x"),new liczba(7))));
    cout << w->opis() << endl;
    zmienna pom = zmienna("asda");
    //petla wypisujaca wszystko co 0.01 zostala okomentowana, zeby nie psuc czytelnosci opisów
    for(double i{0}; i <= 1; i += 0.01){
        pom.ustal("x", i);
        pom.ustal("y", i);
        cout << i << endl;
        cout << jeden->opis() << endl;
        cout << jeden->oblicz() << endl;
        cout << dwa->opis() << endl;
        cout << dwa->oblicz() << endl;
        cout << trzy->opis() << endl;
        cout << trzy->oblicz() << endl;
        cout << cztery->opis() << endl;
        cout << cztery->oblicz() << endl;
    }
    cout << "KONIEC TESTOW Z TRESCI ZADANIA" << endl;
    wyrazenie *testcos = new Cos(new pi());
    cout << testcos->opis() << endl;
    cout << testcos->oblicz() << endl;
    wyrazenie *testsin = new Sin(new pi());
    cout << testsin->opis() << endl;
    cout << testsin->oblicz() << endl;
    wyrazenie *testmod = new Mod(new liczba(3), new liczba(5));
    cout << testmod->opis() << endl;
    cout << testmod->oblicz() << endl;
    wyrazenie* testln = new ln(new Exp(new liczba(7)));
    cout << testln->opis() << endl;
    cout << testln->oblicz() << endl;
}   