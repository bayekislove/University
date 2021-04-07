#include <iostream>
using namespace std;

class tab_bit
{
    typedef uint64_t slowo;
    static const int rozmiarSlowa = 64;
    friend istream &operator>>(istream &we, tab_bit &tb); //done
    friend ostream &operator<<(ostream &wy, const tab_bit &tb);
protected:
    int bitz;
    slowo *tab;
private:
    class ref
    {
    private:
        int pozycja;
        slowo *slowko;
    public:
        ref(slowo *input, int inp);                                 //done
        bool czytaj() const;                                        //done
        void pisz(bool inp);                                        //done
        void operator=(bool k);                                     //done
        friend ostream &operator<<(ostream &out, const ref &input); //done
    };
public:
    explicit tab_bit(int rozmiar);              //done
    explicit tab_bit(unsigned long long input); //done
    tab_bit(initializer_list<int>);            //done
    tab_bit(tab_bit &input);                    //done
    tab_bit(const tab_bit &&input);             //done
    tab_bit &operator=(const tab_bit &tb);      //done
    tab_bit &operator=(tab_bit &&tb);           //done
    ~tab_bit();                                 //done
public:
    bool operator[](int i) const;                               // done
    ref operator[](int i);                                      // done
    inline int rozmiar() const;                                 //done
    friend ostream &operator<<(ostream &out, const ref &input); //done
public:
    tab_bit operator!();                     //done
    tab_bit operator|(const tab_bit &inp);   //done
    tab_bit &operator|=(const tab_bit &inp); //done
    tab_bit &operator&=(const tab_bit &inp); //done
    tab_bit &operator^=(const tab_bit &inp); //done
    tab_bit operator&(const tab_bit &inp);   //done
    tab_bit operator^(const tab_bit &inp);   //done
};