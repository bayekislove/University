using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class5
{
    public class ProcessSingletonProxy
    {
        public static ProcessSingleton GetInstance()
        {
            if(DateTime.Now < Convert.ToDateTime("08:00") || DateTime.Now > Convert.ToDateTime("22:00"))
            {
                throw new TimeoutException();
            }
            return ProcessSingleton.GetInstance();
        }
    }

    public class AirportProxy
    {
        private Airport airport;

        private void Log(string method, params object[] parameters)
        {
            Console.WriteLine("{0} {1}", DateTime.Now, method);
            foreach(var param in parameters)
            {
                Console.Write(" {0} ", param);
            }
        }

        public AirportProxy(int capacity)
        {
            Log("Airport", capacity);
            airport = new Airport(capacity);
        }

        public Plane AcquirePlane()
        {
            Log("AcquirePlane");
            return airport.AcquirePlane();
        }

        public void ReturnPlane(Plane plane)
        {
            Log("ReturnPlane", plane);
            airport.ReturnPlane(plane);
        }
    }
}
