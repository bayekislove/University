#include<iostream>
#include<regex>
#include<string>

using namespace std;

int main()
{
    string thirtyone = "(([0-2][1-9]|30|20|10)-(04|06|09|12)-{?!0000}[0-9]{4})";
    string thirty = "(([0-2][1-9]|30|31|20|10)-(01|03|07|08|10)-{?!0000}[0-9]{4})";
    string twentyeight = "(([0-1][1-9]|2[0-8]|10)-(01|03|07|08|10|12)-{?!0000}[0-9]{4})";

    regex tester("^" + twentyeight + "|" + thirtyone + "|" + thirty  + "$");

    cout << regex_match("12-12-2000", tester) << endl;
    cout << regex_match("29-02-2020", tester) << endl;
    cout << regex_match("31-07-2020", tester) << endl;
    cout << regex_match("-1-05-200", tester) << endl;
    cout << regex_match("10-10--2000", tester) << endl;
    cout << regex_match("32-12-1124", tester) << endl;
    cout << regex_match("02-12-0000", tester) << endl;
}