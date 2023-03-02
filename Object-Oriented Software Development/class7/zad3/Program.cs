using System;
using System.Collections.Generic;
using System.Linq;

namespace zad3
{
    public enum MessageType
    {
        Praise,
        Complaint,
        Order,
        Other
    }

    public interface ISubscriber<T>
    {
        void Handle(T Notification);
    }

    public interface IEventAggregator
    {
        void AddSubscriber<T>(ISubscriber<T> Subscriber);
        void RemoveSubscriber<T>(ISubscriber<T> Subscriber);
        void Publish<T>(T Event);
    }

    public class Archive
    {

    }

    public class EventAggregator : IEventAggregator
    {
        Dictionary<Type, List<object>> _subscribers = new Dictionary<Type, List<object>>();

        public void AddSubscriber<T>(ISubscriber<T> Subscriber)
        {
            if (!_subscribers.ContainsKey(typeof(T)))
                _subscribers.Add(typeof(T), new List<object>());
            _subscribers[typeof(T)].Add(Subscriber);
        }

        public void RemoveSubscriber<T>(ISubscriber<T> Subscriber)
        {
            if (_subscribers.ContainsKey(typeof(T)))
                _subscribers[typeof(T)].Remove(Subscriber);
        }

        public void Publish<T>(T Event)
        {
            if (_subscribers.ContainsKey(typeof(T)))
                foreach (ISubscriber<T> subscriber in _subscribers[typeof(T)].OfType<ISubscriber<T>>())
                    subscriber.Handle(Event);
        }
}

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}
