using System;
using System.Collections.Generic;

namespace class4
{
    public interface IShape
    {
    }

    public interface IShapeFactoryWorker
    {
        public bool AcceptParameters(string shapeName);
        IShape Create(object[] parameters);
    }

    public class ShapeFactory
    {
        private List<IShapeFactoryWorker> workers = new List<IShapeFactoryWorker>();

        public void RegisterWorker(IShapeFactoryWorker worker)
        {
            workers.Add(worker);
        }

        public ShapeFactory()
        {
            workers.Add(new SquareWorker());
            workers.Add(new RectangleWorker());
        }

        public IShape CreateShape(string shapeName, params object[] parameters)
        {
            foreach(var worker in workers)
            {
                if (worker.AcceptParameters(shapeName))
                {
                    return worker.Create(parameters);
                }
            }
            return null;
        }
    }
    
    public class Square : IShape
    {
        public int x { get; set; }
        public Square(int x)
        {
            this.x = x;
        }
    }

    public class SquareWorker : IShapeFactoryWorker
    {
        public bool AcceptParameters(string shapeName)
        {
            return shapeName == "square";
        }

        public IShape Create(object[] parameters)
        {
            if (parameters.Length > 0 && ((parameters[0] as int?) != null))
            {
                return new Square((int)parameters[0]);
            }
            throw new ArgumentException();
        }
    }

    public class Rectangle : IShape
    {
        public int x { get; set; }
        public int y { get; set; }
        public Rectangle(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }

    public class RectangleWorker : IShapeFactoryWorker
    {
        public bool AcceptParameters(string shapeName)
        {
            return shapeName == "rectangle";
        }

        public IShape Create(object[] parameters)
        {
            if (parameters.Length > 1 && ((parameters[0] as int?) != null) && ((parameters[1] as int?) != null))
            {
                return new Rectangle((int)parameters[0], (int)parameters[1]);
            }
            throw new ArgumentException();
        }
    }
}
