using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace _2._4._7
{
    class Program
    {
        static void Main(string[] args)
        {
            //char cha = Console.ReadLine()[0]; żeby nie musieć kompilować dwa razy
            string cha = "B";
            XElement x = XElement.Load("XMLFile1.xml");
            var g = x.Descendants().Where(a => a.Name == "Student");
            var s = g.Where(k => k.Attributes().Any(b => b.Name == "nazwisko" && b.Value.StartsWith(cha)));
            foreach(var person in s)
            {
                Console.WriteLine(person.ToString());
            }
            Console.ReadKey();
        }
    }
}
