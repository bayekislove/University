using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2._3._2
{
    class NewSet : ArrayList
    {
        public NewSet() : base() { }

        public override int Add(object value)
        {
            int search = this.IndexOf(value);
            if( search == -1)
            {
                return base.Add(value);
            }
            return search;
        }
    }
}
