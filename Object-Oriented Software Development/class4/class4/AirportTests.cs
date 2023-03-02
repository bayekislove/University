using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Threading;

namespace class4
{
    [TestClass]
    public class AirportTests
    {
        [TestMethod]
        public void AcquireFirstPlane()
        {
            var airport = new Airport(4);
            Assert.IsNotNull(airport.AcquirePlane());
        }

        [TestMethod]
        public void OutOfBounds()
        {
            var airport = new Airport(0);
            Assert.ThrowsException<ArgumentOutOfRangeException>(() => airport.AcquirePlane());
        }

        [TestMethod]
        public void ReleasePlane()
        {
            var airport = new Airport(4);
            var plane = airport.AcquirePlane();
            airport.ReturnPlane(plane);
            var plane2 = airport.AcquirePlane();
            Assert.AreEqual(plane, plane2);
        }

        [TestMethod]
        public void ReleaseInvalidPlane()
        {
            var airport = new Airport(4);
            var plane = new Plane();
            var plane2 = airport.AcquirePlane();
            Assert.ThrowsException<ArgumentException>(() => airport.ReturnPlane(plane));
        }
    }
}
