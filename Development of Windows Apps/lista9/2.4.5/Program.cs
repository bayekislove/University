using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _2._4._5
{
    class Program
    {
        static void Main(string[] args)
        {
            XmlDocument doc = new XmlDocument();
            doc.LoadXml("<Polak name='Kamil'/>");
            doc.Save("doc.xml");

            XmlDocument doc1 = new XmlDocument();
            doc.Load("XMLFile1.xml");
            doc.Save(Console.Out);
            Console.ReadKey();
        }
    }
}
