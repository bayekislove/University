using System;
using System.Linq;
using System.Collections.Generic;
using System.IO;

namespace _1._3._3
{
    class Program
    {
        static void Main(string[] args)
        {
            List<string> a = new List<string>();
            using (TextReader reader = File.OpenText("TextFile1.txt"))
            {
                string line = reader.ReadLine();
                while (line != null)
                {
                    a.Add(line);
                    line = reader.ReadLine();
                }
            };
            foreach (var k in from name in a
                group name by name[0] into groups
                    orderby groups.Key
                        select groups.Key ){
                Console.WriteLine(k);
            }
            
        }
    }
}
