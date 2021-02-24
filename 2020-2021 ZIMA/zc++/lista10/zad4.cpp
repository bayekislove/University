#include <iostream>
#include <experimental/filesystem>

using namespace std;

namespace exfs = experimental::filesystem;

int main(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        try
        {
            for(const auto & asda : exfs::directory_iterator(argv[i]))
            {
                cout << asda << endl;
            }
        }
        catch(const std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
}