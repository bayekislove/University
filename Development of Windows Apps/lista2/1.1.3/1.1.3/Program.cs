using System;
using System.Reflection;

namespace _1._1._3
{
    class Program
    {
        static void Main(string[] args)
        {

            zad113 zad113test = new zad113();
            zad113test.GetType().GetMethod("Prywata", BindingFlags.NonPublic | BindingFlags.Instance).Invoke(zad113test, null);
            zad113test.GetType().GetProperty("foo", BindingFlags.NonPublic | BindingFlags.Instance).SetValue(zad113test, 3);
            PropertyInfo a = zad113test.GetType().GetProperty("foo", BindingFlags.NonPublic | BindingFlags.Instance);

            Console.WriteLine(a.GetValue(zad113test));

            DateTime Start = DateTime.Now;

            for (int i = 0; i < 10000000; i++)
            {
                zad113test.dostep();
            }
            DateTime End = DateTime.Now;
            Console.WriteLine(End - Start);

            Start = DateTime.Now;
            for (int i = 0; i < 10000000; i++)
            {
                zad113test.GetType().GetMethod("dostep").Invoke(zad113test, null);
            }
            End = DateTime.Now;
            Console.WriteLine(End - Start);

            Console.ReadLine();
        }
    }
}
