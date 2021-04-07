using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

class Osoba
{
    public string konto { get; set; }
    public string pesel { get; set; }
    public string nazwisko { get; set; }
    public string imie { get; set; }

    public override string ToString()
    {
        return imie + " " + nazwisko + " " + pesel + " " + konto;    
    }
}

namespace _1._3._5
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Osoba> imies = new List<Osoba>();
            List<Osoba> kontas = new List<Osoba>();
            using (TextReader reader = File.OpenText("imienazwisko.txt"))
            {
                string line = reader.ReadLine();
                while (line != null)
                {
                    var pom = line.Split();
                    imies.Add( new Osoba() { 
                        imie = pom[0], 
                        nazwisko = pom[1], 
                        pesel = pom[2] 
                    } );
                    line = reader.ReadLine();
                }
            };
            using (TextReader reader = File.OpenText("nrkonta.txt"))
            {
                string line = reader.ReadLine();
                while (line != null)
                {
                    var pom = line.Split();
                    kontas.Add(new Osoba()
                    {
                        pesel = pom[0],
                        konto = pom[1]
                    });
                    line = reader.ReadLine();
                }
            };
            foreach( var p in from imiee in imies
                              join kontt in kontas on imiee.pesel equals kontt.pesel
                              select new {  imie = imiee.imie, 
                                            nazwisko = imiee.nazwisko,
                                            pesel = imiee.pesel,
                                            konto = kontt.konto
                                         }
                              )
            {
                Console.WriteLine(p.ToString());
            }
        }
    }
}
