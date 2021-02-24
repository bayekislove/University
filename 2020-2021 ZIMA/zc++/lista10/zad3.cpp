#include <iostream>
#include <experimental/filesystem>

using namespace std;

namespace exfs = experimental::filesystem;

int main(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        if(exfs::exists(argv[i]))
        {
            cout << "Rozpatrywany plik: " << argv[i] << endl;
            cout << "Jego ścieżka: " << exfs::path(argv[i]) << endl;
            cout << "Jego rozmiar: " << exfs::file_size(argv[i]) << endl;
        }
    }
}