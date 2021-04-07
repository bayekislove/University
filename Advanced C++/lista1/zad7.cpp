#include<iostream>
#include<time.h>
using namespace std;

void wypisz_date(time_t czas){
    cout << gmtime(&czas)->tm_mday << " ";
    switch(auto month = (gmtime(&czas))->tm_mon)
    {
        case 0:
            cout << "styczeń";
            break;
        case 1:
            cout << "luty";
            break;
        case 2:
            cout << "marzec";
            break;
        case 3:
            cout << "kwiecień";
            break;
        case 4:
            cout << "maj";
            break;
        case 5:
            cout << "czerwiec";
            break;
        case 6:
            cout << "lipiec";
            break;
        case 7:
            cout << "sierpień";
            break;
        case 8:
            cout << "wrzesień";
            break;
        case 9:
            cout << "październik";
            break;
        case 10:
            cout << "listopad";
            break;
        case 11:
            cout << "grudzień";
            break;
        default:
            break;
    };
    cout << " " << gmtime(&czas)->tm_year + 1900 << endl;
}

int main(){
    wypisz_date(time(0));
}