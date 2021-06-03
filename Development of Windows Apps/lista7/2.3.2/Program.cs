using System;

namespace _2._3._2
{
    class Program
    {
        static void Main(string[] args)
        {
            NewSet test = new NewSet();
            test.Add(3);
            test.Add(4);
            test.Add(5);
            Console.WriteLine("Skończyłem dodawanie");
            foreach( object a in test)
            {
                Console.WriteLine( a );
            }
            Console.WriteLine("Asda");
            Console.WriteLine(test.IndexOf(4));
            test.Remove(3);
            test.Remove(4);
            test.Remove(5);
            Console.WriteLine(test.Count);
        }
    }
}
