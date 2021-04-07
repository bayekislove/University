using System;
using System.Threading;

namespace _1._4._1
{
    class Program
    {
        static int Foo(int x, int y)
        {
            return x + y;
        }
        static dynamic Foo(dynamic x, dynamic y)
        {
            return x + y;
        }
        static void Main(string[] args)
        {
            int x = 3;
            int y = 4;
            dynamic xd = 3;
            dynamic yd = 4;

            Thread.Sleep(1000);

            DateTime start = DateTime.Now;
            for (int _ = 0; _ < 10000; _++)
            {
                int k = x + y;
            }
            TimeSpan span1 = DateTime.Now - start;

            start = DateTime.Now;
            for (int _ = 0; _ < 10000; _++)
            {
                dynamic s = xd + yd;
            }
            TimeSpan span2 = DateTime.Now - start;
            Console.WriteLine(span2.TotalMilliseconds / span1.TotalMilliseconds);
            //dla 10000000 iteracji dynamic jest 10 razy wolniejszy (7-10 razy)
            //dla 10000 iteracji około 22-25 razy
        }
    }
}
