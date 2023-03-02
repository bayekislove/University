using System;
using System.Threading;

namespace class5
{
    public class ProcessSingleton
    {
        private static ProcessSingleton instance = null;
        private static readonly object locker = 0;

        private ProcessSingleton() { }

        public static ProcessSingleton GetInstance()
        {
            if(instance == null)
            {
                lock (locker)
                {
                    instance = new ProcessSingleton();
                }
            }
            return instance;
        }
    }

    public class ThreadSingleton
    {
        private static ThreadLocal<ThreadSingleton> instance = null;

        ThreadSingleton() { }

        public static ThreadSingleton GetInstance()
        {
            if (instance == null)
            {
                instance = new ThreadLocal<ThreadSingleton>(() => new ThreadSingleton());
            }
            return instance.Value;
        }
    }

    public class TimerSingleton
    {
        private static readonly Timer timer = new Timer(e => UpdateSingleton(), 
                                               null,
                                               TimeSpan.Zero,
                                               TimeSpan.FromSeconds(5));
        private static readonly object locker = 0;
        private static TimerSingleton instance = null;

        TimerSingleton() { }

        private static void UpdateSingleton()
        {
            lock(locker)
            {
                instance = null;
            }
        }

        public static TimerSingleton GetInstance()
        {
            if(instance == null)
            {
                lock(locker)
                {
                    instance = new TimerSingleton();
                }
            }
            return instance;
        }
    }
}
