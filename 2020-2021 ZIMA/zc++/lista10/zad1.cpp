#include<iostream>
#include<vector>
#include<iterator>
#include<iomanip>

using namespace std;

int main()
{
    cout << setprecision(3);

    vector<double> liczby;
    istream_iterator<double> input (cin), eos;
    
    while(input != eos)
    {
        liczby.push_back(*input);
        input++;
    }
    cout << liczby[0] << endl;
    double sum(0.0); 
    for(const auto &x : liczby)
    {
        sum += x;
    }

    double srednia = sum / liczby.size();

    cout << "srednia to " << srednia << endl;

    double counter = 0.0;
    for(const auto &x : liczby)
    {
        counter += (x - srednia) * (x - srednia);
    }

    counter /= liczby.size();
    cout << "odchylenie standardowe to " << counter << endl;
}