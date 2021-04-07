using System.Linq;
using System.Collections.Generic;
using System.IO;
using System;

namespace _1._3._2
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> a = new List<int>();
            using (TextReader reader = File.OpenText("test.txt"))
            {
                string line = reader.ReadLine();
                while( line != null)
                {
                    a.Add( int.Parse(line) );
                    line = reader.ReadLine();
                }
            };
            foreach (var k in from num in a
                              where num <= 100
                              orderby num descending
                              select num )
            {
                Console.WriteLine(k);
            }
            Console.WriteLine();
            foreach (var k in a.Where(x => x <= 100).OrderByDescending( x => x ) )
            {
                Console.WriteLine(k);
            }
            Console.ReadLine();
            //czym roznia sie parametry?
            //funkcje Where i OrderBy przyjmują całe funkcje a where i orderby tylko wyrażenia, które 
            //obliczają się jakby do prawej strony lambda wyrażenia (lewa strona już jest z froma od którego startujemy)
        }
    }
}
