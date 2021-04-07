#include<string>
#include<vector>
#include<iostream>
class wyrazenie{
    public:
        int priorytet = -1;
        bool lewostronnielaczne = 0;
        virtual double oblicz() = 0;
        virtual std::string opis() = 0; 
};

class liczba : public wyrazenie{
    public:
        double wartosc;
        int priorytet;
        liczba(double input);
        std::string opis();
        double oblicz();
}; 

class stala : public wyrazenie{
    protected:
        int priorytet = -1;
        double wartosc;
    public:
        stala(double inp);
        double oblicz();
};

class pi : public stala{
    public:
        std::string opis();
        pi();
};

class e : public stala{
    public:
        std::string opis();
        e();
};

class fi : public stala{
    public:
        std::string opis();
        fi();
};

class zmienna : public wyrazenie{
    private:
        static std::vector<std::pair<std::string, double>> zbior;
    public:
        int priorytet = -1;
        std::string nazwa_zmiennej;
        zmienna(std::string nazwa);
        std::string opis();
        double oblicz(); 
        void ustal(std::string nazwa, double val);
};

class operatorjed : public wyrazenie{
    protected:
        wyrazenie* wyr;
};

class Sin : public operatorjed{
    public:
        Sin(wyrazenie *k);
        std::string opis();
        double oblicz();
};

class Cos : public operatorjed{
    public:
        Cos(wyrazenie *k);
        std::string opis();
        double oblicz();
};

class odwrot : public operatorjed{
    public:
        odwrot(wyrazenie *k);
        std::string opis();
        double oblicz();
};

class Exp : public operatorjed{
    public:
        Exp(wyrazenie *k);
        std::string opis();
        double oblicz();
};

class przeciw : public operatorjed{
    public:
        przeciw(wyrazenie *k);
        std::string opis();
        double oblicz();
};

class ln : public operatorjed{
    public:
        ln(wyrazenie *k);
        std::string opis();
        double oblicz();
};

class bezw : public operatorjed{
    public:
        bezw(wyrazenie *k);
        std::string opis();
        double oblicz();
};

class operatorbin : public operatorjed{
    protected:
        wyrazenie *lewe;
        wyrazenie *prawe;
    public:
        operatorbin(wyrazenie *l, wyrazenie *p);
};

class Dod : public operatorbin{
    public:
        Dod(wyrazenie *l, wyrazenie *p);
        double oblicz();
        std::string opis();
};

class Odejm : public operatorbin{
    public:
        Odejm(wyrazenie *l, wyrazenie *p);
        double oblicz();
        std::string opis();
};

class Mnoz : public operatorbin{
    public:
        Mnoz(wyrazenie *l, wyrazenie *p);
        double oblicz();
        std::string opis();
};

class Dziel : public operatorbin{
    public:
        Dziel(wyrazenie *l, wyrazenie *p);
        double oblicz();
        std::string opis();
};

class Pot : public operatorbin{
    public:
        Pot(wyrazenie *l, wyrazenie *p);
        double oblicz();
        std::string opis();
};

class Log : public operatorbin{
    public:
        Log(wyrazenie *l, wyrazenie *p);
        double oblicz();
        std::string opis();
};

class Mod : public operatorbin{
    public:
        Mod(wyrazenie *l, wyrazenie *p);
        double oblicz();
        std::string opis();
};