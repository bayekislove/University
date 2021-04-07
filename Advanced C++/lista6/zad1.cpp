#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

class Person
{
    public:
        string imie;
        string nazwisko; 
        int wiek;
        int waga;
        int wzrost;

        Person(string im, string naz, int wie, int wag, int wzr)
        {
            imie = im; nazwisko = naz; wiek = wie; waga = wag; wzrost = wzr;
        }

        friend ostream& operator<<(ostream& os, Person inp)
        {
            return os << inp.imie << " " << inp.nazwisko << " " << inp.wiek << " " << inp.waga << " " << inp.wzrost << '\n';
        }
};

void write(deque<Person>& inp)
{
    for(auto x : inp)
    {
        cout << x << endl;
    }
}

void sortBMI(deque<Person>& inp)
{
    sort(inp.begin(), inp.end(), [] (const Person& a, const Person& b) { return a.waga/(a.wzrost / 100.0) < b.waga/(b.wzrost/100.0);} );
    write(inp);
}

void reduceWeight(deque<Person>& inp)
{
    transform(inp.begin(), inp.end(), inp.begin(), [] (Person a) { return Person(a.imie, a.nazwisko, a.wiek, a.waga *= 0.9, a.wzrost); } );
    write(inp);
}

void divideKG(deque<Person>& inp)
{
    partition(inp.begin(), inp.end(), [] (Person a) { return a.waga > 100; });
    write(inp);
}

void minMaxAge(deque<Person>& inp)
{
    auto it = minmax_element(inp.cbegin(), inp.cend(), [] (const Person& a, const Person& b) { return a.wiek < b.wiek; });
    cout << *it.first;
    cout << *it.second;
}

void randomPeople(deque<Person>& inp)
{
    random_shuffle(inp.begin(), inp.end());
    random_shuffle(inp.end() - 5, inp.end());
    write(inp);
}

void midHeight(deque<Person>& inp)
{
    nth_element(inp.begin(), inp.begin() + inp.size() / 2, inp.end(), [] (const Person& a, const Person& b) { return a.wzrost < b.wzrost; });
    write(inp);
}

int main()
{
    deque<Person> test;
    test.push_back(Person("Jarosław", "Kaczyński", 71, 60, 167));
    test.push_back(Person("Mateusz", "Morawiecki", 52, 70, 175));
    test.push_back(Person("Roman", "Giertych", 60, 150, 200));
    test.push_back(Person("Kamil", "Durczok", 40, 300, 300));
    test.push_back(Person("Janusz", "Kowalski", 33, 224, 90));
    test.push_back(Person("Krzysztof", "Bosak", 37, 69, 174));
    test.push_back(Person("Tadeusz", "Mazowiecki", 102, 65, 178));
    test.push_back(Person("Waldemar", "Pawlak", 77, 95, 179));
    test.push_back(Person("Aleks", "Roman", 21, 50, 163));
    test.push_back(Person("Aaa", "BBB", 13, 32, 140));
    test.push_back(Person(":dada", "awdawdawd", 3, 500, 120));

    sortBMI(test); //a
    cout << "\nAAAAAAAAAAAAA \n";
    reduceWeight(test); //b
    cout << "\n BBBBBBBBBBBB \n";
    divideKG(test); //c
    cout << "\n XXXXXX \n";
    midHeight(test); //d
    cout << '\n' << "YYYYYYYYYYYY" << '\n';
    minMaxAge(test); //e
    cout << '\n' << "ADWAWAWDADW" << '\n';
    randomPeople(test); //g
}