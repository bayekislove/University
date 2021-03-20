using System;
using System.Collections.Generic;

namespace _1._2._3
{
    class Program
    {
        static void Main(string[] args)
        {

            List<int> test = new List<int>() { 1, 2, 3, 100, 123, 12, -5 };
            foreach(double x in test.ConvertAll<double>(x => (double)x) )
             {
                Console.WriteLine(x);
            }

            Console.WriteLine();

            foreach (int x in test.FindAll(x => x == 123 || x == 100))
            {
                Console.WriteLine(x);
            }

            Console.WriteLine();

            test.Sort( (int x, int y) => x.CompareTo(y) );
            foreach ( int x in test )
            {
                Console.WriteLine(x);
            }

            Console.WriteLine();

            test.ForEach( delegate (int x) {
                Console.WriteLine(x); }
            );

            Console.WriteLine();

            test.RemoveAll( delegate(int x) { return x > 3; } );
            foreach ( int x in test )
            {
                Console.WriteLine(x);
            }
        }
    }
}
