using System;
using System.Collections.Generic;
using System.Linq;

namespace _1._3._7
{
    class Program
    {
        static void Main(string[] args)
        {
            var item = new { Field1 = "The value", Field2 = 5 };
            var theList = (new[] { item }).ToList();
            theList.Add(new { Field1 = "A", Field2 = 4 });
            Console.WriteLine(theList[1]);
            //theList.Add(new { Field1 = 3, Field2 = 4 }); to spowoduje błąd!
            //theList.Add(new { Field2 = 4, Field1 = "A" }); i to też!
        }
}
}
