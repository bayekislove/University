using System;
using System.Xml;

namespace _2._4._6
{
    class Program
    {
        static void Main(string[] args)
        {
            using (XmlTextWriter a = new XmlTextWriter(Console.Out))
            {
                a.WriteStartElement("root");
                a.WriteAttributeString("item", "3");
                a.WriteEndElement();
            }
            using (XmlTextReader r = new XmlTextReader("XMLFile1.xml"))
            {
                Console.WriteLine(r.Value);
            }

        }
    }
}
