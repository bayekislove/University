#include <iostream>
#include <regex>

using namespace std;

int main()
{
    regex tester("^([0-1]?[0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$");

    cout << regex_match("23:05", tester) << endl;
    cout << regex_match("23:05:1", tester) << endl;
    cout << regex_match("23:056", tester) << endl;
    cout << regex_match("3:05:07", tester) << endl;
}