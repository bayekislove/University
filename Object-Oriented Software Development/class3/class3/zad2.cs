using System;
using System.Collections.Generic;

//docelowo powstaną 3 klasy z jednej klasy ReportPrinter, bo każda z tych nowych klas implementuje jedną 
// funkcjonalność. klasa z metody getData pobiera dane (np. z serwera), klasa formatter formatuje (może to być 
// też użyte przez inną klasę) a klasa print report służy do wyniesienia na wyjście oczekiwanych danych

// nie zawsze każda funkcja musi być inną klasą, kiedy np. mamy funkcje prywatne które służą tylko do czytelności
// kodu możemy je trzymać (a nawet musimy) zawsze obok metod (czyli w tym przypadku metod wyniesionych do klas) 
// do których służą
namespace class3
{
    public class ReportPrinter
    {
        string text;
        public string getData()
        {
            text = "drukarka";
            return text;
        }

        public void FormatDocument()
        {
            text += "\nSformatowano";
        }

        public void printReport()
        {
            Console.WriteLine(text);
        }
    }

    class ReportPrinterRefactored
    {
        public void printReport()
        {
            Console.WriteLine(new Formatter().format(new DataObtainer().obtain()));
        }
    }

    class Formatter
    {
        public string format(string inp)
        {
            return inp + "\nSformatowano";
        }
    }

    class DataObtainer
    {
        public string obtain()
        {
            return "drukarka";
        }
    }
}