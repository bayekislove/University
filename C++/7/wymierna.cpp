#include "wymierna.hpp"

int obliczenia::wymierna::wez_mianownik() const{
    return this->mianownik;
}

int obliczenia::wymierna::wez_licznik() const{
    return this->licznik;
}

int obliczenia::wymierna::gcd(int64_t a, int64_t b){
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

obliczenia::wymierna::wymierna(int licz, int mian){
    if(mian == 0) throw dzielenie_przez_0();
    int gcdd = gcd(licz, mian);
    if(licz * mian < 0){
        this->licznik = (-1) * abs(licz); this->mianownik = abs(mian);
    }
    else{
        this->licznik = abs(licz) / gcdd; this->mianownik = abs(mian) / gcdd;
    }
}

obliczenia::wymierna::wymierna(int licz) : obliczenia::wymierna(licz, 1) {};

obliczenia::wymierna obliczenia::wymierna::operator!() noexcept(false){
    if (this->licznik == 0) throw dzielenie_przez_0();
    return obliczenia::wymierna(this->mianownik, this->licznik);
}

obliczenia::wymierna obliczenia::wymierna::operator-() noexcept(true){
    return obliczenia::wymierna(-1 * this->licznik, this->mianownik);
}

obliczenia::wymierna obliczenia::wymierna::operator*(const wymierna &druga) noexcept(false){
    int64_t nowy_licznik, nowy_mianownik, gcdd;
    nowy_licznik = this->wez_licznik() * druga.wez_licznik();
    nowy_mianownik = this->wez_mianownik() * druga.wez_mianownik();
    gcdd = this->gcd(nowy_licznik, nowy_mianownik);
    nowy_licznik = nowy_licznik / gcdd; nowy_mianownik = nowy_mianownik / gcdd;

    if(nowy_licznik < INT16_MIN || nowy_licznik > INT16_MAX){
        throw przekroczenie_zakresu();
    }
    nowy_mianownik = this->wez_mianownik() * druga.wez_mianownik();
    if(nowy_mianownik < INT16_MIN || nowy_mianownik > INT16_MAX){
        throw przekroczenie_zakresu();
    }
    return obliczenia::wymierna(nowy_licznik, nowy_mianownik);
}

obliczenia::wymierna obliczenia::wymierna::operator/(const wymierna &druga) noexcept(false){
    if(druga.wez_licznik() == 0) throw dzielenie_przez_0();
    int64_t nowy_licznik, nowy_mianownik, gcdd;
    nowy_licznik = this->wez_licznik() * druga.wez_mianownik();
    nowy_mianownik = this->wez_mianownik() * druga.wez_licznik();
    gcdd = this->gcd(nowy_licznik, nowy_mianownik);
    nowy_licznik = nowy_licznik / gcdd; nowy_mianownik = nowy_mianownik / gcdd;
    
    if(nowy_licznik < INT32_MIN || nowy_licznik > INT32_MAX){
        throw przekroczenie_zakresu();
    }   
    if(nowy_mianownik < INT32_MIN || nowy_mianownik > INT32_MAX){
        throw przekroczenie_zakresu();
    }
    return obliczenia::wymierna(nowy_licznik, nowy_mianownik);
}

obliczenia::wymierna obliczenia::wymierna::operator+(const wymierna &druga) noexcept(false){
    int64_t nowy_licznik, nowy_mianownik, gcdd;
    nowy_licznik = this->wez_licznik() * druga.wez_mianownik() + druga.wez_licznik() * this->wez_mianownik();
    nowy_mianownik = this->wez_mianownik() * druga.wez_mianownik();
    gcdd = this->gcd(nowy_licznik, nowy_mianownik);
    nowy_licznik = nowy_licznik / gcdd; nowy_mianownik = nowy_mianownik / gcdd;

    if(nowy_licznik < INT32_MIN || nowy_licznik > INT32_MAX){
        throw przekroczenie_zakresu();
    }   
    if(nowy_mianownik < INT32_MIN || nowy_mianownik > INT32_MAX){
        throw przekroczenie_zakresu();
    }
    return obliczenia::wymierna(nowy_licznik, nowy_mianownik);
}

obliczenia::wymierna obliczenia::wymierna::operator-(const wymierna &druga) noexcept(false){
int64_t nowy_licznik, nowy_mianownik, gcdd;
nowy_licznik = this->wez_licznik() * druga.wez_mianownik() - druga.wez_licznik() * this->wez_mianownik();
nowy_mianownik = this->wez_mianownik() * druga.wez_mianownik();
gcdd = this->gcd(nowy_licznik, nowy_mianownik);
nowy_licznik = nowy_licznik / gcdd; nowy_mianownik = nowy_mianownik / gcdd;

if(nowy_licznik < INT32_MIN || nowy_licznik > INT32_MAX){
    throw przekroczenie_zakresu();
    }   
if(nowy_mianownik < INT32_MIN || nowy_mianownik > INT32_MAX){
    throw przekroczenie_zakresu();
    }
return obliczenia::wymierna(nowy_licznik, nowy_mianownik);
}

obliczenia::wymierna::operator double(){
    return double(this->licznik) / double(this->mianownik);
};

obliczenia::wymierna::operator int(){
    if(double(*this) - 0.5 >= this->licznik/this->mianownik){
        return this->licznik/this->mianownik + 1;  };
    return this->licznik/this->mianownik;
};

std::ostream& obliczenia::operator<<(std::ostream &out, const obliczenia::wymierna &inp){
    std::vector<int> wynik;
    std::vector<int> reszty;
    if(inp.wez_licznik() < 0){
        out << "-";
    }

    int reszta = abs(inp.wez_licznik()) % inp.wez_mianownik();
    out << int(abs(inp.wez_licznik()) / inp.wez_mianownik());

    if (reszta == 0) {  
        return out;
    }
    reszty.push_back(reszta);
    out << ".";
    while(true){
        wynik.push_back(reszta * 10 / inp.wez_mianownik());
        reszta = reszta * 10 % inp.wez_mianownik();
        if(reszta == 0){
            for(int i = 0; i < wynik.size(); i++){
                out << wynik[i];
            }
            return out;
        }
        for(int j{0}; j < wynik.size(); j++){ //szukamy czy reszty juz sie nie powtorzyly
            if(reszty[j] == reszta){
                for(int k{0}; k < j; k++){
                    out << wynik[k];
                }
                out << "(";
                for(int k{0}; k< reszty.size(); k++){
                    out << wynik[k];
                }
                out << ")"; 
                return out;
            }
        }
        reszty.push_back(reszta);
    }
}