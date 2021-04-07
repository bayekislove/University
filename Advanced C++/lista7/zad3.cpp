#include<iostream>
#include<fstream>
#include<random>
using namespace std;

random_device gen;

void writeFile(string name, int length)
{
    ofstream writee;
    writee.open(name);

                                    //A,     B    C     D      E      F      G   H    I         J    K
    discrete_distribution<int> dis{14810, 2715, 4943, 7874, 21912, 4200, 3693, 10795, 13318, 188, 1257, 
                                   // L,  M     N      O     P      R    S       T     V    W         X    Y       Z 
                                    7253, 4761, 12666, 14003, 3316, 10977, 11450, 16587, 2019, 3819, 315, 3853, 128};

    binomial_distribution<int> wordLengthGen(11, 0.5);

    int counter = 0;
    while( counter < length)
    {
        int asda = wordLengthGen(gen) + 1;

        while( !(counter + asda < length ))
            asda = wordLengthGen(gen) + 1;

        for(int i = 0; i < asda; i++)
        {
            writee << static_cast<char>(dis(gen) + 97);
        }

        counter += asda;
        if(counter < length) 
        {
            writee << ' ';
            counter++;
        }
    }
}

int main(int argc, char *argv[])
{
    writeFile("zad3.txt", 100);
}