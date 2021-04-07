using System;
using System.Collections.Generic;
using System.Reflection;

namespace _1._1._4
{
    class Program
    {
        static void Attributes(object o)
        {
            MethodInfo[] start = o.GetType().GetMethods( BindingFlags.Public | BindingFlags.Instance );
            List<MethodInfo> mi = new List<MethodInfo>();

            foreach( MethodInfo mii in start )
                if( mii.ReturnType == typeof(int) && mii.GetParameters().Length == 0  ) 
                    mi.Add(mii);

            foreach ( MethodInfo a in mi)
            {
                foreach( Attribute b in a.GetCustomAttributes())
                {
                    if( b.GetType() == typeof(OznakowaneAttribute) )
                        Console.WriteLine(a.Invoke(o, null) );
                }
            }
        }

        static void Main(string[] args)
        {
            Attributes(new Foo());
        }
    }
}
