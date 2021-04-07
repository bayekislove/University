using System;

namespace zad2
{
    class Program
    {
        static void Main(string[] args)
        {
            Grid test = new Grid(2, 2);
            test[0, 0] = 0;
            test[0, 1] = 1;
            test[1, 0] = 2;
            test[1, 1] = 3;

            Console.WriteLine( test[0][1] );
            Console.WriteLine( test[1][1] );
        }
    }
}
