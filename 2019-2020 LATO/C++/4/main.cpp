#include "stos.cpp"
int main(){
    stos a(7);
    a.wloz("asda");
    cout << a.sprawdz() << '\n';
    cout << a.rozmiar() << '\n';
    a.zdejmij();
    cout << a.sprawdz() << '\n';
    cout << a.rozmiar() << '\n';
    a.wloz("asd1");
    a.wloz("asd2");
    stos c({"gasda", "kada"});
    cout << c.rozmiar() << endl;
    cout << c.zdejmij() << endl;
    stos b;
    b = a;
    cout << b.rozmiar() << '\n';
    cout << a.zdejmij() << endl;
    cout << b.zdejmij() << endl;
    stos e;
    e = (stos({"x", "y", "z"})).odwroc();
    cout << e.rozmiar() << endl;
    cout << e.zdejmij() << endl;
    cout << e.zdejmij() << endl;
    cout << e.zdejmij() << endl;
}