#include<iostream>
#include<limits>

using namespace std;

int main(){
    cout << numeric_limits<float>::max() << endl;
    cout << numeric_limits<double>::max() << endl;
    cout << numeric_limits<float>::epsilon() << endl;
    cout << numeric_limits<double>::epsilon() << endl;
    cout << numeric_limits<double>::denorm_min() << endl;
    cout << numeric_limits<float>::denorm_min() << endl;
}