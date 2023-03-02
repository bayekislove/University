using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class5
{
    class Adapter<T> : IComparer
    {
        Comparison<T> comparison;

        public Adapter(Comparison<T> comparison)
        {
            this.comparison = comparison;
        }

        public int Compare(object x, object y)
        {
            return comparison((T)x, (T)y);
        }
    }
}
