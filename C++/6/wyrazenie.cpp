#include "wyrazenie.hpp"
#include<math.h>
using namespace std;

vector<pair<string, double>> zmienna::zbior;

liczba::liczba(double input){
    priorytet = -1;
    this->wartosc = input;
}

string liczba::opis(){
    return to_string(wartosc);
}

double liczba::oblicz(){
    return wartosc;
}

stala::stala(double k){
    wartosc = k;
}

double stala::oblicz(){
    return wartosc;
}
 
pi::pi() : stala(3.1415926535897) {}

string pi::opis(){
    return "π";
}

e::e() : stala(2.71828182845) {}

string e::opis(){
    return "e";
}

fi::fi() : stala(1.61803398874) {}

string fi::opis(){
    return "φ";
}

zmienna::zmienna(string nazwa){
    priorytet = -1;
    nazwa_zmiennej = nazwa;
    bool jest;
    for(int i{0}; i < zmienna::zbior.size(); i++){
        if (zmienna::zbior[i].first == nazwa){
            zbior.erase(zbior.begin() + i);
        }
    }
    if(jest == false){
        zmienna::zbior.push_back(make_pair(nazwa, 0));
    }
}

string zmienna::opis(){
    return nazwa_zmiennej;
}

double zmienna::oblicz(){
    for(int i{0}; i < zmienna::zbior.size(); i++){
        if (zmienna::zbior[i].first == nazwa_zmiennej){
            return zmienna::zbior[i].second;
        }
    }
}

void zmienna::ustal(string inp, double val){
    bool jest;
    for(int i{0}; i < zmienna::zbior.size(); i++){
        if (zmienna::zbior[i].first == inp){
            zbior.erase(zbior.begin() + i);
        }
    }
    if(jest == false){
        zmienna::zbior.push_back(make_pair(inp, val));
    }
};

Sin::Sin(wyrazenie *k){
    priorytet = -1;
    wyr = k;
}

string Sin::opis(){
    return "sin(" + wyr->opis() + ")";
}

double Sin::oblicz(){
    return sin(wyr->oblicz());
}

Cos::Cos(wyrazenie *k){
    priorytet = -1;
    wyr = k;
}

string Cos::opis(){
    return "cos(" + wyr->opis() + ")";
}

double Cos::oblicz(){
    return cos(wyr->oblicz());
}

przeciw::przeciw(wyrazenie *k){
    priorytet = -1;
    wyr = k;
}

string przeciw::opis(){
    return "-(" + wyr->opis() + ")";
}

double przeciw::oblicz(){
    return (-1) * wyr->oblicz();
}

odwrot::odwrot(wyrazenie *k){
    priorytet = -1;
    wyr = k;
}

string odwrot::opis(){
    return "1/(" + wyr->opis() + ")";
}

double odwrot::oblicz(){
    return 1 / wyr->oblicz();
}

Exp::Exp(wyrazenie *k){
    priorytet = -1;
    wyr = k;
}

string Exp::opis(){
    return "exp(" + wyr->opis() + ")"; 
}

double Exp::oblicz(){
    return exp(wyr->oblicz());
}

ln::ln(wyrazenie *k){
    priorytet = -1;
    wyr = k;
}

string ln::opis(){
    return "ln(" +  wyr->opis() + ")";
}

double ln::oblicz(){
    return log(wyr->oblicz());
}

bezw::bezw(wyrazenie *k){
    priorytet = -1;
    wyr = k;
}

string bezw::opis(){
    return "|" + wyr->opis() + "|";
}

double bezw::oblicz(){
    if(wyr->oblicz() >= 0){
        return wyr->oblicz();
    }
    else{
        return -1 * wyr->oblicz();
    }
}

operatorbin::operatorbin(wyrazenie *l, wyrazenie *p){
    lewe = l; prawe = p;
}

Dod::Dod(wyrazenie *l, wyrazenie *p) : operatorbin(l, p){
    lewostronnielaczne = 1; priorytet = 1;
}

double Dod::oblicz(){
    return lewe->oblicz() + prawe->oblicz();
}

string Dod::opis(){
    string templeft, tempright;
    if((lewe->priorytet == -1) || (lewe->priorytet > this->priorytet)) {
        templeft = lewe->opis();
    }
    else if(lewe->priorytet < this->priorytet){
        templeft = "(" + lewe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        templeft = lewe->opis();
    }
    else{
        templeft = "(" + lewe->opis() + ")";
    }
    if((prawe->priorytet == -1) || (prawe->priorytet > this->priorytet)) {
        tempright = prawe->opis();
    }
    else if(prawe->priorytet < this->priorytet){
        tempright = "(" + prawe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        tempright = prawe->opis();
    }
    else{
        tempright = "(" + prawe->opis() + ")";
    }
    return templeft + "+" + tempright;
}

Odejm::Odejm(wyrazenie *l, wyrazenie *p) : operatorbin(l, p) {
    lewostronnielaczne = 1; priorytet = 1;
}

double Odejm::oblicz(){
    return lewe->oblicz() - prawe->oblicz();
}

string Odejm::opis(){
    string templeft, tempright;
    if((lewe->priorytet == -1) || (lewe->priorytet > this->priorytet)) {
        templeft = lewe->opis();
    }
    else if(lewe->priorytet < this->priorytet){
        templeft = "(" + lewe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        templeft = lewe->opis();
    }
    else{
        templeft = "(" + lewe->opis() + ")";
    }
    if((prawe->priorytet == -1) || (prawe->priorytet > this->priorytet)) {
        tempright = prawe->opis();
    }
    else if(prawe->priorytet < this->priorytet){
        tempright = "(" + prawe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 0){
        tempright = prawe->opis();
    }
    else{
        tempright = "(" + prawe->opis() + ")";
    }
    return templeft + "-" + tempright;
}

Mnoz::Mnoz(wyrazenie *l, wyrazenie *p) : operatorbin(l, p){
    priorytet = 2; lewostronnielaczne = 1;
}

double Mnoz::oblicz(){
    return lewe->oblicz() * prawe->oblicz();
}

string Mnoz::opis(){
    string templeft, tempright;
    if(lewe->priorytet == -1){
        templeft = lewe->opis();
    }
    else if(lewe->priorytet > this->priorytet){
        templeft = lewe->opis();
    }
    else if(lewe->priorytet < this->priorytet){
        templeft = "(" + lewe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        templeft = lewe->opis();
    }
    else{
        templeft = "(" + lewe->opis() + ")";
    }
    if((prawe->priorytet == -1) || (prawe->priorytet > this->priorytet)) {
        tempright = prawe->opis();
    }
    else if(prawe->priorytet < this->priorytet){
        tempright = "(" + prawe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        tempright = prawe->opis();
    }
    else{
        tempright = "(" + prawe->opis() + ")";
    }
    return templeft + "*" + tempright;
}

Dziel::Dziel(wyrazenie *l, wyrazenie *p) : operatorbin(l, p){
    priorytet = 2; lewostronnielaczne = 1;
}

double Dziel::oblicz(){
    if(prawe->oblicz() == 0){
        throw invalid_argument("Nie dzielimy przez 0!");
    }
    return lewe->oblicz() / prawe->oblicz();
}

string Dziel::opis(){
    string templeft, tempright;
    if((lewe->priorytet == -1) || (lewe->priorytet > this->priorytet)) {
        templeft = lewe->opis();
    }
    else if(lewe->priorytet < this->priorytet){
        templeft = "(" + lewe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        templeft = lewe->opis();
    }
    else{
        templeft = "(" + lewe->opis() + ")";
    }
    if((prawe->priorytet == -1) || (prawe->priorytet > this->priorytet)) {
        tempright = prawe->opis();
    }
    else if(prawe->priorytet < this->priorytet){
        tempright = "(" + prawe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        tempright = prawe->opis();
    }
    else{
        tempright = "(" + prawe->opis() + ")";
    }
    return templeft + "/" + tempright;
}

Pot::Pot(wyrazenie *l, wyrazenie *p) : operatorbin(l, p){
    priorytet = 3; lewostronnielaczne = 0;
}

double Pot::oblicz(){
    return pow(lewe->oblicz(), prawe->oblicz());
}

string Pot::opis(){
    string templeft, tempright;
    if((lewe->priorytet == -1) || (lewe->priorytet > this->priorytet)) {
        templeft = lewe->opis();
    }
    else if(lewe->priorytet < this->priorytet){
        templeft = "(" + lewe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        templeft = lewe->opis();
    }
    else{
        templeft = "(" + lewe->opis() + ")";
    }
    if((prawe->priorytet == -1) || (prawe->priorytet > this->priorytet)) {
        tempright = prawe->opis();
    }
    else if(prawe->priorytet < this->priorytet){
        tempright = "(" + prawe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        tempright = prawe->opis();
    }
    else{
        tempright = "(" + prawe->opis() + ")";
    }
    return templeft + "^" + tempright;
}

Log::Log(wyrazenie *l, wyrazenie *p) : operatorbin(l, p){
    priorytet = 3; lewostronnielaczne = 0;
}

double Log::oblicz(){
    return log(prawe->oblicz()) / log(lewe->oblicz()); //ze wzoru na zamiane podstawy logarytmu
}

string Log::opis(){
    return "log(p" + lewe->opis() + "ll" + prawe->opis() + ")";
}

Mod::Mod(wyrazenie *l, wyrazenie *p) : operatorbin(l, p){
    priorytet = 2; lewostronnielaczne = 0;
}

double Mod::oblicz(){
    if(prawe->oblicz() == 0){
        throw invalid_argument("Nie da się wziąć modulo 0!");
    }
    return lewe->oblicz() - prawe->oblicz() * (floor(lewe->oblicz() / prawe->oblicz()));
}

string Mod::opis(){
    string templeft, tempright;
    if((lewe->priorytet == -1) || (lewe->priorytet > this->priorytet)) {
        templeft = lewe->opis();
    }
    else if(lewe->priorytet < this->priorytet){
        templeft = "(" + lewe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        templeft = lewe->opis();
    }
    else{
        templeft = "(" + lewe->opis() + ")";
    }
    if((prawe->priorytet == -1) || (prawe->priorytet > this->priorytet)) {
        tempright = prawe->opis();
    }
    else if(prawe->priorytet < this->priorytet){
        tempright = "(" + prawe->opis() + ")";
    }
    else if(this->lewostronnielaczne == 1){
        tempright = prawe->opis();
    }
    else{
        tempright = "(" + prawe->opis() + ")";
    }
    return templeft + "%" + tempright; 
}