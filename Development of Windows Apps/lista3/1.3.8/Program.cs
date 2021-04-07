using System;
using System.Collections.Generic;
using System.Linq;

namespace _1._3._8
{
    class Program
    {
        delegate Func<A, R> Rec<A, R>(Rec<A, R> r);
        static Func<A, R> Y<A, R>(Func<Func<A, R>, Func<A, R>> f)
        {
            Rec<A, R> rec = r => a => f(r(r))(a);
            return rec(rec);
        }

        static void Main(string[] args)
        {
            List<int> list = new List<int>() { 1, 2, 3, 4, 5 };
            foreach (var item in
            list.Select( i => Y<int, int>(f => n => n > 1 ? f(n - 1) + f(n - 2) : n)(i) ) )
            {
                Console.WriteLine(item);
            }
        }
    }
}
