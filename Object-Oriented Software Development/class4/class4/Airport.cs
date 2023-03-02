using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class4
{
    class Airport
    {
        private int capacity;
        private List<Plane> ready = new List<Plane>();
        private List<Plane> released = new List<Plane>();

        public Airport(int capacity)
        {
            this.capacity = capacity;
        }

        public Plane AcquirePlane()
        {
            if (capacity <= 0)
            {
                throw new ArgumentOutOfRangeException();
            }
            if(ready.Count == 0)
            {
                ready.Add(new Plane());
            }
            var plane = ready[0];
            ready.Remove(plane);
            released.Add(plane);
            capacity--;
            return plane;
        }

        public void ReturnPlane(Plane plane)
        {
            if (!released.Contains(plane))
            {
                throw new ArgumentException();
            }
            released.Remove(plane);
            ready.Add(plane);
            capacity++;
        }
    }

    class Plane
    {

    }
}
