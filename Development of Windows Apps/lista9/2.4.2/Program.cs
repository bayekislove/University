using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Schema;

namespace _2._4._2
{
    class Program
    {
        static void Main(string[] args)
        {
            XmlSchemaSet a = new XmlSchemaSet();
            a.Add("lista8", "XMLFile1.xsd");
            XmlReader rd = XmlReader.Create("XMLFile1.xml");
            XDocument doc = XDocument.Load(rd);
            doc.Validate(a, (object sender, ValidationEventArgs e) => { throw new Exception(e.Message); } );
        }
    }
}
