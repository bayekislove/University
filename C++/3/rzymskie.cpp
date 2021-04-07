#include <iostream>
#include <vector>
#include <string>
using namespace std;

string bin2rom(int x){
    const vector<pair<int, string>> rzym = {
    {1000, "M"},
    {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
    {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"},
    {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    string wynik = "";
    for(int i{0}; i < rzym.size(); i++){
        if(x - rzym[i].first >= 0){
            wynik = wynik + rzym[i].second;
            x = x - rzym[i].first;
            i--;
        }   
    }
    return wynik;
};
int main(int argc, char *argv[]){
    for(int i{1}; i < argc; i++){
        int liczba{-1};
        try{
            liczba = stoi(argv[i]);
            if((liczba>3999) || (liczba<=0)){
                liczba = -1;
                clog << "Proszę podać dodatnią liczbę naturalną mniejszą od 3999!\n";
            }
        }
        catch(invalid_argument){
            clog << "Proszę podać dodatnią liczbę naturalną mniejszą od 3999!\n";
        }
        if(liczba > 0){
            
            cout << bin2rom(liczba) << "\n";
        }
    }
}

