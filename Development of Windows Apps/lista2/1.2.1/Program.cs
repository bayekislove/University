using System;
using System.Collections.Generic;
using System.Collections;

namespace _1._2._1
{
    class Program
    {
        static void Main(string[] args)
        {
            Random r = new Random();
            List<int> testL = new List<int>();

            DateTime Start = DateTime.Now;
            for( int i = 0; i < 30000000; i++)
            {
                testL.Add( i );
            }
            DateTime End = DateTime.Now;
            TimeSpan Czas = End - Start;

            Console.WriteLine("Czas dodania elementów do List: {0}ms", Czas.TotalMilliseconds);
            ArrayList testAL = new ArrayList(); 

            Start = DateTime.Now;
            for (int i = 0; i < 30000000; i++)
            {
                testAL.Add(i);
            }
            End = DateTime.Now;
            Czas = End - Start;

            Console.WriteLine("Czas dodania elementów do ArrayList: {0}ms", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            for (int i = 0; i < 100000; i++)
            {
                testL.IndexOf( i );
            }
            End = DateTime.Now;
            Czas = End - Start;

            Console.WriteLine("Czas przejrzenia List {0}ms", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            for (int i = 0; i < 100000; i++)
            {
                testAL.IndexOf(i);
            }
            End = DateTime.Now;
            Czas = End - Start;

            Console.WriteLine("Czas przejrzenia ArrayList {0}ms", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            for (int i = 0; i < 100000; i++)
            {
                testL.Add(i);
            }
            End = DateTime.Now;
            Czas = End - Start;

            Console.WriteLine("Czas usunięcia z List: {0}ms", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testAL.Add(i);
            }
            End = DateTime.Now;
            Czas = End - Start;
            Console.WriteLine("Czas usunięcia z ArrayList: {0}ms", Czas.TotalMilliseconds);

            Hashtable testH = new Hashtable();

            Start = DateTime.Now;
            
            for (int i = 0; i < 10000000; i++)
            {
                testH.Add(i, i);
            }
            End = DateTime.Now;
            Czas = End - Start;

            Console.WriteLine("Czas dodania do Hashtable {0}ms", Czas.TotalMilliseconds);

            Dictionary<int, int> testD = new Dictionary<int, int>();
            Start = DateTime.Now;
            
            for (int i = 0; i < 10000000; i++)
            {
                testD.Add(i, i);
            }
            End = DateTime.Now;
            Czas = End - Start;

            Console.WriteLine("Czas dodania do Dictionary {0}ms", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            
            for (int i = 0; i < 10000000; i++)
            {
                testH.Contains(i);
            }
            End = DateTime.Now;
            Czas = End - Start;

            Console.WriteLine("Czas przeszukania Hashtable {0}ms", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testD.ContainsKey(i);
            }
            End = DateTime.Now;
            Czas = End - Start;
            Console.WriteLine("Czas przeszukania Dictionary {0}ms", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testH.Remove(i);
            }
            End = DateTime.Now;
            Czas = End - Start;
            Console.WriteLine("Czas usunięcia z Hashtable {0}ms", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testD.Remove(i);
            }
            End = DateTime.Now;
            Czas = End - Start;
            Console.WriteLine("Czas usunięcia z Dictionary {0}ms", Czas.TotalMilliseconds);
        }
    }
}
