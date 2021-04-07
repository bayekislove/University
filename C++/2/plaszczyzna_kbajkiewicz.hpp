#include <iostream>

class Wektor{
    public:
        const double dx, dy;
        Wektor() = default; // konstruktor domyślny
        Wektor(double x, double y); 
        Wektor(const Wektor&);
};

class Punkt{
    public:
        const double x, y;
        Punkt() = default;
        Punkt(double a, double b); 
        Punkt(const Wektor w, const Punkt p); 
        Punkt(const Punkt&); //konstruktor kopiujący
};

class Prosta{
    private:
        double a, b, c;
    public:
        Prosta(double x, double y, double z); 
        Prosta(const Punkt x, const Punkt y); 
        Prosta() = default;
        Prosta(const Wektor w); 
        Prosta(Prosta l, const Wektor k);
        Prosta & operator= (Prosta&) = delete; // to sprawi, ze klasa jest niekopowionalna
        double getA(); 
        double getB(); 
        double getC(); 
        bool czy_wektor_prostopadly(const Wektor w); 
        bool czy_punkt_lezy(const Punkt p); 
        bool czy_wektor_rownolegly(const Wektor k);
};