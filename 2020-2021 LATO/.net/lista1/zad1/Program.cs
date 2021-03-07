using System;
using System.Collections.Generic;

namespace zad1
{
    class Program
    {
        static bool correct(uint y)
        {
            uint x = y;
            uint numSum = 0; 
            while( x > 0 )
            {
                numSum += x % 10;
                if (x % 10 == 0 || y % (x % 10) != 0)
                    return false;
                x /= 10;
            }
            return y % numSum == 0;
        }

        static void Main(string[] args)
        {
            List<uint> divs = new List<uint>();

            for(uint i = 1; i <= 100000; i++)
            {
                if( correct(i))
                {
                    divs.Add( i );
                    Console.WriteLine(i);
                }
            }
            Console.WriteLine( $"Takich liczb jest {divs.Count}" );
        }
    }
}
