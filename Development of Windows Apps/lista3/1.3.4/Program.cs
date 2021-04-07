using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace _1._3._4
{
    class Program
    {
        static void Main(string[] args)
        {
            string folder = @"tester";
            var size = Directory.GetFiles(folder).Select(x => new FileInfo(x).Length).Aggregate((a, b) => a + b );
            Console.WriteLine(size);
        }
    }
}
