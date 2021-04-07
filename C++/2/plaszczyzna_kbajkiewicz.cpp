#include <iostream>
#include "plaszczyzna_kbajkiewicz.hpp"
using namespace std;

Punkt::Punkt(double a, double b):
    x(a), y(b) {}

Punkt::Punkt(const Wektor w, const Punkt p):
  x(p.x + w.dx), y(p.y + w.dy) {}

Punkt::Punkt(const Punkt& p):
    y(p.y), x(p.x) {}

Wektor skladanie(const Wektor wektor1, const Wektor wektor2){
    double wsp1, wsp2;
    wsp1 = wektor1.dx + wektor2.dx;
    wsp2 = wektor1.dy + wektor2.dy;
    Wektor a(wsp1, wsp2);
    return a;
}

Wektor::Wektor(const Wektor& p):
    dy(p.dy), dx(p.dx) {}

Wektor::Wektor(double x, double y):
    dx(x), dy(y){}

Prosta::Prosta(const Punkt x, const Punkt y){
    if((x.x == y.x) || (x.y == y.y)){
        throw invalid_argument("Proszę podać dwa róźne punkty!");
    }
    a = (x.y - y.y) / (x.x - y.x);
    b = 1;
    c = x.y - ((x.y - y.y) / (x.x - y.x) * (y.x));
};

Prosta::Prosta(const Wektor w){
    double a_wektora;
    a_wektora = w.dy / w.dx;
    a = -1 / a_wektora;
    b = 1;
    c = w.dy - this->a * w.dx;
};

Prosta::Prosta(double x, double y, double z){
    if(x == 0 || y == 0){
        throw invalid_argument("A i B nie mogą być jednocześnie zerowe!");
    }
    a = x;
    b = y;
    c = z;
};

Prosta::Prosta(Prosta l, const Wektor k){
    a = l.getA(); b = l.getB();
    c = k.dy * b - k.dx * a; 
}

double Prosta::getA(){
    return a;
};

double Prosta::getB(){
    return b;
};

double Prosta::getC(){
    return c;
}

bool Prosta::czy_punkt_lezy(const Punkt p){
    double a, b, c;
    a = this->a; b = this->b; c=this->c;
    if(a*p.x + b*p.y + c == 0){
        return true;
    }
    return false;
}

bool Prosta::czy_wektor_rownolegly(const Wektor k){
    double A, B, aw;
    A = this->a; B=this->b;
    aw = k.dx / k.dy;
    if(aw == -A/B){
        return true;
    }
    return false;
}

bool Prosta::czy_wektor_prostopadly(const Wektor k){
    double A, B, aw;
    A = this->a; B=this->b;
    aw = k.dx / k.dy;
    if(aw * (A/B) == -1){
        return true;
    }
    return false;
}

bool czy_rownolegle(Prosta l1, Prosta l2){
    double a1, b1, a2, b2;
    a1 = l1.getA(); b1 = l1.getB(); a2 = l2.getA(); b2 = l2.getB();
    if(a1*b2 == a2*b1){
        return true;
    }
    return false;
}

bool czy_prostopadle(Prosta l1, Prosta l2){
    double a1, b1, a2, b2;
    a1 = l1.getA(); b1 = l1.getB(); a2 = l2.getA(); b2 = l2.getB();
    if(a1*a2 / (b1*b2) == -1){
        return true;
    }
    return false;
}

Punkt punkt_przeciecia(Prosta l1, Prosta l2){
    if(czy_rownolegle(l1, l2)){
        throw invalid_argument("Proszę podać proste przecinające się w różnej od zera, skończonej liczbie punktów");
    }
    double a1, a2, b1, b2, c1, c2;
    a1 = l1.getA(); a2 = l2.getA(); b1 = l1.getB(); b2 = l2.getB(); c1 = l1.getC(); c2 = l2.getC();
    double x, y;
    x = ((c2*b1) - (c1*b2)) / ((a1*b2) - (a2*b1));
    y = (-1/b1)*((a1*x)-c1);
    Punkt przeciecie(x, y);
    return przeciecie;
}

int main(){
    Punkt k(1, 3);
    cout << k.x << endl;
    Wektor a(1, 2);
    Wektor b(2, 3);
    Wektor c = skladanie(a, b);
    cout << c.dx << endl;
    Prosta l1(1, 1, 3);
    Prosta l2(-1, 70, 3);
    cout << czy_rownolegle(l1, l2) << endl;
    Prosta l3(1,1,1);
    Prosta l4(-1,1,1);
    cout << czy_prostopadle(l3, l4) << endl;
    cout << "Testowanie sprawdzania pkt przecięcia: " << punkt_przeciecia(l3, l4).x << "  " << punkt_przeciecia(l3, l4).y << endl;
    Punkt p1(0,2);
    Punkt p1_copy(p1);
    cout << "Testowanie przypisania kopiującego: " << p1.x << " " << p1_copy.x << " " << p1.y << " " << p1_copy.y << endl;
    cout << l3.czy_punkt_lezy(p1_copy) << endl;
    Prosta l5(a);
    cout << l5.getA() << "   " << l5.getB() << "   " << l5.getC() << endl;
}

