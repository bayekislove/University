#include "wymierna.hpp"
#include <string>
  
int main(){
    using namespace obliczenia;
    using namespace std;
    wymierna test(8,3);
    wymierna test1(-1,3);
    cout << "8/3 / (-1/3) " << test / test1 << endl;
    cout << "8/3 * (-1/3) " << test * test1 << endl;
    cout << "8/3 - (-1/3) " << test - test1 << endl;
    cout << "8/3 + (-1/3) " << test + test1 << endl;
    cout << "Rzutowanie na double -1/3 " << double(test1) << endl;
    cout << "Rzutowanie na int 8/3 " << int(test) << endl;
    cout << "Rozwinięcie dziesiętne " << test1 << endl; 
}
