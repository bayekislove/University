#include<iostream>
#include<algorithm>
#include<fstream>
#include<array>
using namespace std;


string getFileToString(ifstream& stm)
{
    return string((std::istreambuf_iterator<char>(stm)),
                  (std::istreambuf_iterator<char>()));
}

int main(int argc, const char *argv[])
{
    ifstream File(argv[1]);
    string read = getFileToString(File);

    std::array<uint, 26> counts{0};
    for_each(read.begin(), read.end(), 
            [&] (const char &let) {
                    if(let >= 'A' && let <= 'Z')
                        counts[let - 65] += 1;
                    else if(let >= 'a' && let <= 'z')
                        counts[let - 97] += 1; });

    uint allLettersCounted = 0;
    for_each(counts.begin(), counts.end(), [&] (uint &c) { allLettersCounted += c; });

    for(int i = 'a'; i <= 'z'; i++)
    {   
        cout << static_cast<char>(i) << ": " << counts[i - 97] / double(allLettersCounted) << ";" << endl;
    }
}