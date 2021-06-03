using System;
using System.IO;
using System.Reflection;

namespace _2._3._10
{

    public class Resourcer
    {
        public static string getResource(string name)
        {

            using (Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream("_2._3._10." + name))
            using (StreamReader sRead = new StreamReader(stream))
            {
                return sRead.ReadToEnd();
            }

        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.Write(Resourcer.getResource("zad.txt"));
            Console.ReadLine();
        }
    }
}
