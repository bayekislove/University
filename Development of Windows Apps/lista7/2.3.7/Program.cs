using System;
using System.Messaging;

namespace _2._3._7
{
    public class Manager
    {
        Random a = new Random();

        public void create()
        {
            using (MessageQueue mq = new MessageQueue(".\\myQueue"))
            {
                mq.Send( new Message() { Body = a.Next().ToString() } ); //składnik zewnętrzny zgłosił wyjątek - o co chodzi :(((((
            }
        }
    }

    public class Worker
    {
        public void manage()
        {
            using(MessageQueue mq = new MessageQueue(".\\myQueue"))
            {
                Message m = mq.Receive();
                long k = 0;
                for(int i = 0; i < 1000000; i++)
                {
                    k = i * i << 2;
                }
                Console.WriteLine(m.Body.ToString());
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Worker w = new Worker();
            Manager m = new Manager();
            while (true)
            {
                for(int i = 0; i < 10; i++)
                {
                    m.create();
                }
                for(int i = 0; i < 6; i++)
                {
                    w.manage();
                }
            }
        }
    }
}
