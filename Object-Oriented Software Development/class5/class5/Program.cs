using System;
using System.Collections;

namespace class5
{
    class Program
    {
        static void Main(string[] args)
        {
            ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };

            Comparison<int> comparison = (x, y) => x.CompareTo(y);
            a.Sort(new Adapter<int>(comparison));

            Array.ForEach<object>(a.ToArray(), Console.WriteLine);
        }
    }
}
