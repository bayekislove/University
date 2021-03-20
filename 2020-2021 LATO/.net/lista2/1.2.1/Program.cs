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
            DateTime End = DateTime.Now;
            for( int i = 0; i < 30000000; i++)
            {
                testL.Add( i );
            }
            TimeSpan Czas = Start - End;

            Console.WriteLine("Czas dodania elementów do List: {0}", Czas.TotalMilliseconds);
            ArrayList testAL = new ArrayList(); 

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 30000000; i++)
            {
                testAL.Add(i);
            }
            Czas = Start - End;

            Console.WriteLine("Czas dodania elementów do ArrayList: {0}", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 100000; i++)
            {
                testL.IndexOf( i );
            }
            Czas = Start - End;

            Console.WriteLine("Czas przejrzenia List {0}", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 100000; i++)
            {
                testAL.IndexOf(i);
            }
            Czas = Start - End;

            Console.WriteLine("Czas przejrzenia ArrayList {0}", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 100000; i++)
            {
                testL.Add(i);
            }
            Czas = Start - End;

            Console.WriteLine("Czas usunięcia z List: {0}", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testAL.Add(i);
            }
            Czas = Start - End;
            Console.WriteLine("Czas usunięcia z ArrayList: {0}", Czas.TotalMilliseconds);

            Hashtable testH = new Hashtable();

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testH.Add(i, i);
            }
            Czas = Start - End;

            Console.WriteLine("Czas dodania do Hashtable {0}", Czas.TotalMilliseconds);

            Dictionary<int, int> testD = new Dictionary<int, int>();
            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testD.Add(i, i);
            }
            Czas = Start - End;

            Console.WriteLine("Czas dodania do Dictionary {0}", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testH.Contains(i);
            }
            Czas = Start - End;

            Console.WriteLine("Czas przeszukania Hashtable {0}", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testD.ContainsKey(i);
            }
            Czas = Start - End;
            Console.WriteLine("Czas przeszukania Dictionary {0}", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testH.Remove(i);
            }
            Czas = Start - End;
            Console.WriteLine("Czas usunięcia z Hashtable {0}", Czas.TotalMilliseconds);

            Start = DateTime.Now;
            End = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                testD.Remove(i);
            }
            Czas = Start - End;
            Console.WriteLine("Czas usunięcia z Dictionary {0}", Czas.TotalMilliseconds);
        }
    }
}
