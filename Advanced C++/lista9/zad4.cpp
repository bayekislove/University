#include<iostream>
#include<regex>

using namespace std;

int main()
{
    regex tester(R"(^[+-]?\d+(\.\d+)? *\+ *[+-]?\d+(\.\d+)?[iI]$)");

    cout << regex_match("3+2i", tester) << endl;
    cout << regex_match("3.1 + 2i", tester) << endl;
    cout << regex_match("3+2.5I", tester) << endl;
}