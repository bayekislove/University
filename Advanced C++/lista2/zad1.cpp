#include<iostream>
#include<memory>
#include<cstdint>
#include<ctime>

class licznik{
    public:
        uint64_t c_licznik;
    
    licznik(){ c_licznik = 1; };

    virtual ~licznik(){
        std::cerr << c_licznik << std::endl;
    }
};

void rec_inc(int i, int m, int n, std::unique_ptr<licznik[]> &licznik_tab){
    if(m == 0) return;
    for(int j = 0; j < n; j++){
        if(rand() % 2 == 0)
            licznik_tab[j].c_licznik += i;
    }
    rec_inc(i+1, m-1, n, licznik_tab);
}

int main(){
    int n = 5;
    std::srand(time(nullptr));
    std::unique_ptr<licznik[]> licznik_tab = std::make_unique<licznik[]>(n);
    rec_inc(1, n, n, licznik_tab);
}