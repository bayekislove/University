#include<iostream>
#include<fstream>
#include<regex>
#include<string>

using namespace std;

int main()
{
    smatch hiper;
    ifstream fileContent("zad5.html");
    string fileLine;
    string fileSaved = "";

    while(getline(fileContent, fileLine)) 
    {  
        fileSaved += fileLine;
    };

    while(regex_search(fileSaved, hiper, regex(R"(<a +href *= *".*" *> *)"))){
        fileSaved = fileSaved.substr(hiper.position());
        string temp = fileSaved.substr(fileSaved.find(R"(")") + 1);
        fileSaved = fileSaved.substr(fileSaved.find('>') + 1);

        cout << temp.substr(0, temp.find(R"(")")) << endl;
    }
}