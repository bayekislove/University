#include "tab_bit.hpp"
#include <string>

using namespace std;

tab_bit::tab_bit(int rozmiar)
{
    bitz = rozmiar;
    tab = new slowo[(rozmiar / rozmiarSlowa) + 1];
    for (int i{0}; i < (rozmiar / rozmiarSlowa) + 1; i++)
    {
        tab[i] = 0;
    }
}

tab_bit::tab_bit(unsigned long long input)
{
    tab = new slowo[0];
    tab[0] = input;
    bitz = rozmiarSlowa;
}

tab_bit::tab_bit(tab_bit &input)
{
    this->bitz = input.bitz;
    tab = new slowo[(input.bitz / rozmiarSlowa) + 1];
    for (int i{0}; i < (this->bitz / rozmiarSlowa) + 1; i++)
    {
        this->tab[i] = input.tab[i];
    }
}

tab_bit::tab_bit(const tab_bit &&input) : tab(input.tab), bitz(input.bitz) {}

tab_bit::tab_bit(initializer_list<int> input){
    bitz = input.size();
    tab = new slowo[(int(input.size()) / rozmiarSlowa) + 1];
    int i{0};
    for(initializer_list<int>::iterator it = input.begin(); it < input.end(); it++){
        tab_bit::ref pom(&tab[i / rozmiarSlowa], i % rozmiarSlowa);
        pom.pisz(*it);
        i++;
    }
}

tab_bit &tab_bit::operator=(tab_bit &&tb)
{
    this->tab = tb.tab;
    this->bitz = tb.bitz;
    tb.tab = nullptr;
    tb.bitz = 0;
    return *this;
}

tab_bit &tab_bit::operator=(const tab_bit &tb)
{
    tab = new slowo[(tb.rozmiar() / rozmiarSlowa) + 1];
    this->bitz = tb.rozmiar();
    for (int i{0}; i < (this->bitz / rozmiarSlowa) + 1; i++)
    {
        this->tab[i] = tb.tab[i];
    }
    return *this;
}

tab_bit::~tab_bit()
{
    this->bitz = 0;
    delete[] tab;
}

tab_bit::ref::ref(slowo *input, int inp)
{
    this->slowko = input;
    this->pozycja = inp;
}

bool tab_bit::ref::czytaj() const
{
    return (*slowko >> this->pozycja) & 1;
}

void tab_bit::ref::pisz(bool inp)
{
    if (inp == 1)
    {
        *slowko = (1 << this->pozycja) | *slowko;
    }
    if (inp == 0)
    {
        *slowko = *slowko & (~(1 << this->pozycja));
    }
}

int tab_bit::rozmiar() const
{
    return this->bitz;
}

bool tab_bit::operator[](int indeks) const
{
    if (indeks >= this->bitz)
    {
        throw invalid_argument("index out of range");
    }
    return (tab_bit::ref(&tab[indeks / 64], indeks % 64)).czytaj();
}

tab_bit::ref tab_bit::operator[](int indeks)
{
    if (indeks >= this->bitz)
    {
        throw invalid_argument("index out of range");
    }
    return (tab_bit::ref(&tab[indeks / 64], indeks % 64));
}

void tab_bit::ref::operator=(bool inp)
{
    pisz(inp);
}

ostream &operator<<(ostream &out, const tab_bit::ref &input)
{
    out << input.czytaj();
    return out;
}

//istream & operator >> (istream &instream,tab_bit::ref &input){
// instream >> input.pisz();
//return instream;
//}

ostream &operator<<(ostream &wy, const tab_bit &tb)
{
    string pom;
    for (int i{0}; i < tb.rozmiar(); i++)
    {
        tab_bit::ref help(&tb.tab[i / tb.rozmiarSlowa], i % tb.rozmiarSlowa);
        if (help.czytaj() == 0)
        {
            pom = pom + '0';
        }
        else
        {
            pom = pom + '1';
        }
    }
    wy << pom;
    return wy;
}

tab_bit tab_bit::operator!()
{
    tab_bit wynik(this->rozmiar());
    for (int i = 0; i < this->bitz; i++)
    {
        ref pom(&this->tab[i / rozmiarSlowa], i % rozmiarSlowa);
        ref end(&wynik.tab[i / rozmiarSlowa], i % rozmiarSlowa);
        end.pisz(!pom.czytaj());
    }
    return wynik;
}

tab_bit &tab_bit::operator|=(const tab_bit &inp)
{
    for (int i = 0; i < min(inp.rozmiar(), this->rozmiar()); i++)
    {
        ref pom(&tab[i / rozmiarSlowa], i % rozmiarSlowa);
        ref pom2(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
        pom.pisz(pom.czytaj() | pom2.czytaj());
    }
    return *this;
}

tab_bit tab_bit::operator|(const tab_bit &inp)
{
    tab_bit k(max(this->rozmiar(), inp.rozmiar()));
    if (this->rozmiar() <= inp.rozmiar())
    {
        for (int i{0}; i < this->rozmiar(); i++)
        {
            tab_bit::ref pom1(&this->tab[i / rozmiarSlowa], i % rozmiarSlowa);
            tab_bit::ref pom2(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            tab_bit::ref wynik(&k.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            wynik.pisz(pom1.czytaj() | pom2.czytaj());
        }
        for (int i = this->rozmiar(); i < inp.rozmiar(); i++)
        {
            (ref(&k.tab[i / rozmiarSlowa], i % 64)).pisz(ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa).czytaj());
        }
    }
    else
    {
        for (int i{0}; i < inp.rozmiar(); i++)
        {
            ref pom1 = ref(&this->tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref pom2 = ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref wynik = ref(&k.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            wynik.pisz(pom1.czytaj() | pom2.czytaj());
        }
        for (int i{inp.rozmiar()}; i < this->rozmiar(); i++)
        {
            (ref(&k.tab[i / rozmiarSlowa], i % 64)).pisz(ref(&this->tab[i / rozmiarSlowa], i % rozmiarSlowa).czytaj());
        }
    }
    return k;
}

tab_bit tab_bit::operator&(const tab_bit &inp)
{
    tab_bit k(max(this->rozmiar(), inp.rozmiar()));
    if (this->rozmiar() <= inp.rozmiar())
    {
        for (int i = 0; i < this->rozmiar(); i++)
        {
            ref pom1 = ref(&tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref pom2 = ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref wynik = ref(&k.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            wynik.pisz(pom1.czytaj() & pom2.czytaj());
        }
        for (int i{this->rozmiar()}; i < inp.rozmiar(); i++)
        {
            (ref(&k.tab[i / rozmiarSlowa], i % 64)).pisz(ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa).czytaj());
        }
    }
    else
    {
        for (int i{0}; i < inp.rozmiar(); i++)
        {
            ref pom1 = ref(&tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref pom2 = ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref wynik = ref(&k.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            wynik.pisz(pom1.czytaj() & pom2.czytaj());
        }
        for (int i{this->rozmiar()}; i < this->rozmiar(); i++)
        {
            (ref(&k.tab[i / rozmiarSlowa], i % 64)).pisz(ref(&this->tab[i / rozmiarSlowa], i % rozmiarSlowa).czytaj());
        }
    }
    return k;
}

tab_bit tab_bit::operator^(const tab_bit &inp)
{
    tab_bit k(max(this->rozmiar(), inp.rozmiar()));
    if (this->rozmiar() <= inp.rozmiar())
    {
        for (int i{0}; i < this->rozmiar(); i++)
        {
            ref pom1 = ref(&tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref pom2 = ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref wynik = ref(&k.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            wynik.pisz(pom1.czytaj() ^ pom2.czytaj());
        }
        for (int i{this->rozmiar()}; i < inp.rozmiar(); i++)
        {
            (ref(&k.tab[i / rozmiarSlowa], i % 64)).pisz(ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa).czytaj());
        }
    }
    else
    {
        for (int i{0}; i < inp.rozmiar(); i++)
        {
            ref pom1 = ref(&tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref pom2 = ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            ref wynik = ref(&k.tab[i / rozmiarSlowa], i % rozmiarSlowa);
            wynik.pisz(pom1.czytaj() ^ pom2.czytaj());
        }
        for (int i{this->rozmiar()}; i < this->rozmiar(); i++)
        {
            (ref(&k.tab[i / rozmiarSlowa], i % 64)).pisz(ref(&this->tab[i / rozmiarSlowa], i % rozmiarSlowa).czytaj());
        }
    }
    return k;
}

tab_bit &tab_bit::operator&=(const tab_bit &inp)
{
    for (int i = 0; i < min(inp.rozmiar(), this->rozmiar()); i++)
    {
        ref pom = ref(&tab[i / rozmiarSlowa], i % rozmiarSlowa);
        ref pom2 = ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
        pom.pisz(pom.czytaj() & pom2.czytaj());
    }
    return *this;
}

tab_bit &tab_bit::operator^=(const tab_bit &inp)
{
    for (int i = 0; i < min(inp.rozmiar(), this->rozmiar()); i++)
    {
        ref pom = ref(&tab[i / rozmiarSlowa], i % rozmiarSlowa);
        ref pom2 = ref(&inp.tab[i / rozmiarSlowa], i % rozmiarSlowa);
        pom.pisz(pom.czytaj() ^ pom2.czytaj());
    }
    return *this;
}
