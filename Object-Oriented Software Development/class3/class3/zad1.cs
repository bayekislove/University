/* Ten kod spełnia następujące zasady GRASP:
 * Creator - Sieć jest zobowiązana do stworzenia A, bo zapamiętuje o niej informacje
 * Law of Demeter - nie zmuszamy uzytkownika do pisania siec.szef.menedzer, tylko mamy metode ktora to zwraca
   wobec tego jesli np. chcielibysmy szefem zrobic jakiegos kierownika tylko części sieci (czyli dodali klasę
   Szef regionalny), to użytkownik nie musiałby o tym wiedzieć - metoda ktoSzefem() zwróci mu nowego kierownika
 * Information Expert - nie pytamy oddzialu o liczbe oddzialow, bo nie musi ich znac - liczbe oddzialow zna siec
 * Low Coupling - Oddzial nie musi znac szefa, skoro zna swoja siec a ta zna szefa
 */

using System;
using System.Collections.Generic;

namespace class3
{
    class Sieć
    {
        List<Oddział> oddziały;
        Szef szef;

        public Sieć()
        {
            oddziały = new List<Oddział>();
            szef = new Szef() { menedzer = "Kamil" };
        }

        public Oddział stworzOddzial()
        {
            Oddział od = new Oddział(oddziały.Count, this);
            oddziały.Add(od);
            return od;
        }

        public string ktoSzefem()
        {
            return this.szef.menedzer;
        }

        public int ileOddzialow()
        {
            return this.oddziały.Count;
        }
    }

    class Oddział
    {
        int numer;
        Sieć siec;

        public Oddział(int numer, Sieć siec)
        {
            this.numer = numer;
            this.siec = siec;
        }

        public int numerOddziału()
        {
            return numer;
        }

        public string szef()
        {
            return siec.ktoSzefem();
        }
    }

    class Szef
    {
        public string menedzer;
    }
}
