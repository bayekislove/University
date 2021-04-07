#include<iostream>
#include<memory>

class zad3{
    public:
        zad3(){
            std::cout << "Zad3 otworzono" << std::endl;
        }

        ~zad3(){
            std::cout << "Zad3 zniszczono" << std::endl;
        }
};

int main(){
    std::weak_ptr<zad3> t1; //nie zwieksza licznika referencji
    std::shared_ptr<zad3> t2; //zwieksza licznik referencji
 
    {
        std::shared_ptr<zad3> p1 = std::make_shared<zad3>();
        t2 = p1;
    }   
    std::cout<<"asda"<< std::endl;
}