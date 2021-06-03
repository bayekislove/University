using System;
using System.Collections.Generic;
using System.Threading;

namespace ConsoleApp1
{
    class Program
    {
        static List<Client> bench = new List<Client>();
        static Barber g = new Barber(bench);

        static void Main(string[] args)
        {
            Thread t1 = new Thread(new ThreadStart(g.sleep));
            Thread t2 = new Thread(new ThreadStart(waitRoom));

            t1.Start();
            t2.Start();
        }

        public static void waitRoom() //jak zrobić żeby podać ThreadStartowi funkcję która bierze argument?
        {
            Random r = new Random();
            while (true)
            {
                new Client(g, bench);
                int n = r.Next(1, 2);
                Thread.Sleep(n * 100);
            }
        }
    }

    class Client
    {
        public Client(Barber g, List<Client> l)
        {
            if (g.sleeping)
                g.wake(this);
            else
                l.Add(this);
        }
    }

    class Barber
    {
        public bool sleeping;
        public Client currClient;
        public List<Client> l;

        public Barber(List<Client> l)
        {
            this.l = l;
            sleeping = true;
            currClient = null;
        }

        public void wake(Client k)
        {
            sleeping = false;
            currClient = k;
        }

        public void sleep()
        {
            while (sleeping)
            {
                Thread.Sleep(200);
            }
            work();
        }

        public void work()
        {
            Thread.Sleep(2000);
            if (l.Count > 0)
            {
                currClient = l[0];
                l.RemoveAt(0);
                work();
            }
            else
            {
                sleeping = true;
                sleep();
            }
        }
    }
}