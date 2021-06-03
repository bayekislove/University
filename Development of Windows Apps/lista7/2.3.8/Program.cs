using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;

namespace _2._3._8
{
    class Program
    {
        static void Main(string[] args)
        {
            List<string> cultures = new List<string>() { "en", "de", "fr", "ru", "ar", "cs", "pl" };

            foreach( string c in cultures)
            {
                CultureInfo cul = new CultureInfo(c);

                var dateFormat = cul.DateTimeFormat;
                string[] months = dateFormat.MonthNames;
                string[] shortened = dateFormat.AbbreviatedMonthNames;
                for (int i = 0; i < 12; i++)
                    Console.WriteLine(months[i] + " " + shortened[i]);

                string[] days = dateFormat.DayNames;
                shortened = dateFormat.AbbreviatedDayNames;
                for (int i = 0; i < 7; i++)
                    Console.WriteLine(days[i] + " " + shortened[i]);

                DateTime pom = DateTime.Now;

                Console.WriteLine($"{pom.Year} {months[pom.Month - 1]} {pom.Day}");
                Console.WriteLine();
            }
        }
    }
}
