using System;

namespace _1._1._4
{
    public class Foo
    {
        [OznakowaneAttribute]
        public int Bar()
        {
            return 1;
        }
        public int Qux()
        {
            return 2;
        }
        private int Syf()
        {
            return 3;
        }
    }

    public class OznakowaneAttribute : Attribute
    {
    }
}
