//Kacper Bajkiewicz zad 4 lista 1
using System.Collections.Generic;
using System;
namespace zad4
{
    class LeniwaLista{
        public List<int> tablica = new List<int>();
        public static int rozmiar;
        public LeniwaLista(){
            rozmiar = 0;
        }
        public virtual int element(int i){
            if(i - 1 >=rozmiar){
                for(int k = rozmiar; k <= i - 1; k++){
                    Random random = new Random();
                    tablica.Add(random.Next(-7000000, 70000000));
                    rozmiar += 1;
                }
            }
            return tablica[i-1];
        }
        public int size(){
            return rozmiar;
        }
        public class Pierwsze : LeniwaLista
            {
            private bool czy_pierwsza(int liczba){
                for(int a = 2; a < Math.Sqrt(liczba); a++){
                    if(liczba % a == 0){
                        return false;
                    }
                }
                return true;
            }
            public override int element(int pierwszy){
                if(pierwszy >= rozmiar){
                    int iterator = 2;
                    if(rozmiar == 0){
                        iterator = 2;
                    }
                    else if(tablica[rozmiar-1] < 2){
                        iterator = 2;
                    }
                    else{
                        iterator = tablica[rozmiar-1] + 1;
                    }
                    while(rozmiar != pierwszy){
                        if(czy_pierwsza(iterator) == true){
                            rozmiar += 1;
                            tablica.Add(iterator);
                        }
                        iterator += 1;
                    }
                }
                return tablica[pierwszy - 1];
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            LeniwaLista test = new LeniwaLista();
            Console.WriteLine(test.size());
            test.element(70);
            Console.WriteLine(test.size());
            Console.WriteLine(test.element(65));
            Console.WriteLine(test.element(100));
            Console.WriteLine(test.element(65));
            Console.WriteLine("Teraz testuję podklasę z liczbami pierwszymi:");
            LeniwaLista.Pierwsze testowa = new LeniwaLista.Pierwsze();
            Console.WriteLine(testowa.size());
            Console.WriteLine(testowa.element(30));
            Console.WriteLine(testowa.element(40));
            Console.WriteLine(testowa.element(30));
            Console.WriteLine()
        }
    }
    
}
