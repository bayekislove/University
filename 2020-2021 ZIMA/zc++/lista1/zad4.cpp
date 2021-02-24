#include<iostream>
using namespace std;

enum class name : uint16_t {
    Kasia,
    Arek,
    Krzysztof
};

void exclamation(string text, name who){
    switch (who)
    {
    case name::Arek:
        cout << "Arku, " << text << endl;
        break;
    case name::Krzysztof:
        cout << "Krzysztofie, " << text << endl;
        break;
    case name::Kasia:
        cout << "Kasiu, " << text << endl;
        break;
    default:
        cout << "Nie znam tej osoby" << endl;
        break;
    }
}

int main(){
    exclamation("na pewno głosujesz na PiS", name::Krzysztof);
}