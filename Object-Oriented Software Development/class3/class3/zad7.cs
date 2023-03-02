using System;

namespace class3
{
    namespace zad7
    {
        class ReportPrinterRefactored
        {
            public Action<string> printer;
            public void printReport(string inp)
            {
                printer(inp);
            }
        }

        class Formatter
        {
            public Func<string, string> formatter;
            public string format(string inp)
            {
                return formatter(inp);
            }
        }

        class DataObtainer
        {
            public Func<string> obtainer;
            public string obtain()
            {
                return obtainer();
            }
        }
        public class ReportComposer
        {
            ReportPrinterRefactored reporter = new ReportPrinterRefactored() { printer = x => Console.WriteLine(x) };
            Formatter formatter = new Formatter() { formatter = x => x + "\nSformatowano" };
            DataObtainer obtainer = new DataObtainer() { obtainer = () => "AAAA" };

            public void get()
            {
                reporter.printReport(formatter.format(obtainer.obtain()));
            }
        }

        class zad7
        {
            static void Main(string[] args)
            {

            }
        }
    }
}
