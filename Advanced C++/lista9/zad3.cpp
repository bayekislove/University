#include<iostream>
#include<regex>

using namespace std;

int main()
{
    regex tester("^([A-Z][a-z]* *)*(-[A-Z][a-z]*)?(( *[A-Z][a-z]*)*)?$");

    cout << regex_match("Ustronie", tester) << endl;
    cout << regex_match("Szczecin-Dolny", tester) << endl;
    cout << regex_match("Duże Miasto", tester) << endl;
    cout << regex_match("Szczecin-Dolny-Górny", tester) << endl;
    cout << regex_match("Mały Szczecin-Dolny", tester) << endl;
}