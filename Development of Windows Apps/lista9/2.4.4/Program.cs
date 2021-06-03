using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace _2._4._4
{
    public class AdresStaly
    {
        public string miasto { get; set; }
    }

    public class AdresTymczasowy
    {
        public string miasto { get; set; }
    }

    public class ListaZajec
    {
        public List<Przedmiot> przedmioty { get; set; }
    }

    public class Przedmiot
    {
        public string name { get; set; }
    }

    public class Student
    {
        public string imie { get; set; }
        public string nazwisko { get; set; }
        public AdresStaly aS {get; set;}
        public AdresTymczasowy aT { get; set; }
        public ListaZajec lz { get; set; }
    }

    public class ListaStudentow
    {
        string nazwa { get; set; }
        public List<Student> l { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {

            StringReader xml = new StringReader(File.ReadAllText("XMLFile1.xml"));
            XmlSerializer ser = new XmlSerializer(typeof(ListaStudentow));

            ListaStudentow l = (ListaStudentow)ser.Deserialize(xml);
            Console.ReadKey();
        }
    }
}
