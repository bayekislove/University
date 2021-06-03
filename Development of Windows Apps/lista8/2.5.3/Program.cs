using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Runtime.InteropServices;
using System.Data.Linq;

namespace _2._5._3
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var data = new StudenciDataContext(@"server=.\sqlexpress;database=Studenci;integrated security=true"))
            {
                if (data.Students.Where(x => x.Imie == "A").Take(1).Select(x => x).Count() > 0)
                {
                    data.Students.DeleteOnSubmit(data.Students.Where(x => x.Imie == "A").Take(1).Select(x => x).First());
                    data.SubmitChanges();
                }

                Miejscowosc m1 = new Miejscowosc() { Nazwa = "SZN" };
                data.Miejscowoscs.InsertOnSubmit(m1);
                data.SubmitChanges();

                //dodawanie studenta
                Student nowy = new Student() { Imie = "A", Nazwisko = "B", DataUr = DateTime.Parse("01/11/1970") };
                nowy.Miejscowosc = m1;
                data.Students.InsertOnSubmit(nowy);
                data.SubmitChanges();

                Student ozenilSie = data.Students.Where(x => x.Imie == "A").Take(1).Select(x => x).First();
                ozenilSie.Nazwisko = "Ozeniony";
                data.SubmitChanges();

            }
            Console.ReadLine();
        }
    }
}
