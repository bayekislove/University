using System;

namespace _2._3._1
{
    class Complex : IFormattable
    {
        private readonly int Re;
        private readonly int Im;

        public Complex(int Re, int Im)
        {
            this.Re = Re;
            this.Im = Im;
        }

        public static Complex operator +(Complex a, Complex b) => new Complex(a.Re + b.Re, a.Im + b.Im);

        public static Complex operator -(Complex a, Complex b) => new Complex(a.Re - b.Re, a.Im - b.Im);

        public static Complex operator *(Complex a, Complex b) => new Complex(a.Re*b.Re - a.Im*b.Im, a.Im*b.Re + a.Re*b.Im);

        //dzielenie do zrobienia

        public override string ToString()
        {
            return Re.ToString() + " + " + Im.ToString() + "i";
        }

        public string ToString(string format)
        {
            return ToString(null, null);
        }

        public string ToString(string format, IFormatProvider formatProvider)
        {
            if (format == "d" || format == null)
                return Re.ToString() + " + " + Im.ToString() + "i";
            if (format == "w")
                return "[" + Re.ToString() + ", " + Im.ToString() + "]";
            return "Nieznane formatowanie";
        }
    }
}
