using System;

namespace class3
{
    public class Rectangle : Square
    {
        public override void setWidth(int w)
        {
            this.Width = w;
        }
        public override void setHeight(int h)
        {
            this.Height = h;
        }
    }
    public class Square
    {
        protected int Width; //zeby nie moc zmienic z zewnatrz
        protected int Height;

        public int getWidth()
        {
            return Width;
        }

        public virtual void setWidth(int w)
        {
            Width = w;
            Height = w;
        }

        public virtual void setHeight(int h)
        {
            Width = h;
            Height = h;
        }

        public int getHeight()
        {
            return Height;
        }
    }

    class Program
    {
        public class AreaCalculator
        {
            public int CalculateArea(Square rect)
            {
                return rect.getHeight() * rect.getWidth();
            }
        }

        static void Mainn(string[] args)
        {
            int w = 4, h = 5;
            Square rect = new Rectangle();
            rect.setWidth(w);
            rect.setHeight(h);
            AreaCalculator calc = new AreaCalculator();
            Console.WriteLine("prostokąt o wymiarach {0} na {1} ma pole {2}", w, h, calc.CalculateArea(rect));
            Console.ReadKey();
        }
    }
}
