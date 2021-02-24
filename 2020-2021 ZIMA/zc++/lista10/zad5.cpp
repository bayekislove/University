#include <iostream>
#include <experimental/filesystem>

using namespace std;
namespace exfs = experimental::filesystem;

int main(int argc, char* argv[])
{
    long long int sum = 0;
    for(int i = 1; i < argc; i++)
    {
        for( const auto & asda : exfs::recursive_directory_iterator(argv[i]) )
        {
            try
            {
                if( exfs::is_regular_file(asda) ) 
                    sum += exfs::file_size(asda);
            }
            catch(const std::exception& e) { }
        }
    }
    cout << "Suma wszystkich plików w folderach i podfolderach to: " << sum << "B" << endl;
}