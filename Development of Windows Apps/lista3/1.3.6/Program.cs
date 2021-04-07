using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace _1._3._6
{
    class Program
    {
        static void Main(string[] args)
        {
            List<string> a = new List<string>();
            using (TextReader reader = File.OpenText("tester.txt"))
            {
                string line = reader.ReadLine();
                while (line != null)
                {
                    a.Add(line.Split()[1]);
                    line = reader.ReadLine();
                }
            };

            foreach( var k in ( from ip in a
                                group ip by ip into counter
                                orderby counter.Count() descending
                                select counter.Key + " " + counter.Count() )
                                .Take(3) )
            {
                Console.WriteLine(k);
            }
        }
    }
}
