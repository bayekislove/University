#include <iostream>
#include <string>
#include <vector>

namespace obliczenia{

    class wymierna{
        private:
            int licznik;
            int mianownik;
            int gcd(int64_t a, int64_t b); //done
            friend std::ostream &operator<<(std::ostream &out, const wymierna &inp);
        public:
            wymierna(int licz, int mian); //done
            wymierna(int licz);           //done
            int wez_licznik() const;      //done
            int wez_mianownik() const;    //done
            wymierna operator!(); //działa
            wymierna operator-() noexcept; //działa
            wymierna operator* (const wymierna &druga); //done
            wymierna operator/ (const wymierna &druga); //done
            wymierna operator- (const wymierna &druga); //done
            wymierna operator+ (const wymierna &druga); //done
            operator double(); //done
            operator int(); //done
            
    };

    class wyjatekwymierny : std::exception {};
    class dzielenie_przez_0 : wyjatekwymierny {};
    class przekroczenie_zakresu : wyjatekwymierny {};

}

