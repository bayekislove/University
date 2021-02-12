#include<iostream>
#include<math.h>
using namespace std;

void rozwiazania(double a, double b, double c){
    if(double delta = pow(b, 2) - 4*a*c; delta < 0){
        cout << "Brak miejsc zerowych rzeczywistych" << endl;
    }
    else if(double delta = pow(b, 2) - 4*a*c; delta == 0){
        cout << -b / (2*a) << endl;
    }
    else{
        cout << (-b - sqrt(delta))/(2*a) << endl;
        cout << (-b + sqrt(delta))/(2*a) << endl;
    }
}

int main(){
    rozwiazania(1, 4, 4);
}