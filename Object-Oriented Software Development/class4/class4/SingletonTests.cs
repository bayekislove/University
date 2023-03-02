using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Threading;

namespace class4
{
    [TestClass]
    public class SingletonTests
    {
        [TestMethod]
        public void IfProcessSingletonGivesSameInstance()
        {
            var singleton1 = ProcessSingleton.GetInstance();
            var singleton2 = ProcessSingleton.GetInstance();
            Assert.AreEqual(singleton1, singleton2);
        }

        [TestMethod]
        public void IfThreadSingletonGivesSameInstance()
        {
            ThreadSingleton singleton1 = null;
            ThreadSingleton singleton2 = null;
            Thread t1 = new Thread(() => singleton1 = ThreadSingleton.GetInstance());
            Thread t2 = new Thread(() => singleton2 = ThreadSingleton.GetInstance());
            t1.Start();
            t2.Start();
            t1.Join();
            t2.Join();
            Assert.AreNotEqual(singleton1, singleton2);
        }

        [TestMethod]
        public void IfTimeSingletonGivesSameInstance()
        {
            TimerSingleton timer1 = TimerSingleton.GetInstance();
            Thread.Sleep(7000);
            TimerSingleton timer2 = TimerSingleton.GetInstance();
            Assert.AreNotEqual(timer1, timer2);
        }
    }
}
