using System;

namespace _1._4._2
{
    class Program
    {
        static void Main(string[] args)
        {
            Type wordType = Type.GetTypeFromProgID("Word.Application");
            Type wordDoc = Type.GetTypeFromProgID("Word.Document");
            dynamic w = Activator.CreateInstance(wordType);
            dynamic doc = w.Documents.Add();

            w.Visible = true;
            doc.Range(0, 0).Text = "Programowanie pod Windows";
            doc.SaveAs("ppw.doc");
            doc.Close();
            //dokument zapisuje się na dysku w folderze Dokumenty, ten wygenerowany na moim komputerze
            //wrzucam do głównego folderu zadania
        }
    }
}
