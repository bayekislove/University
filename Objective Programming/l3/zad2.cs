using System;

namespace nowy
{
    public class Slownik<K,V>{
        private K[] klucze;
        private V[] wartosci;
        private int size;
        public Slownik(){
            klucze = new K[1];
            wartosci = new V[1];
            size = 0;
        }
        public V search(K klucz){
            for(int i = 0; i < size; i++){
                if(Equals(klucze[i],klucz)){
                    return wartosci[i];
                }
            }
            return default(V);
        }
        public int get_size(){
            return size;
        }
        public void Add(K klucz, V wartosc){
            if(this.size != 0){
                Array.Resize(ref klucze, size+1);
                Array.Resize(ref wartosci, size+1);
                klucze[size] = klucz;
                wartosci[size] = wartosc;
            }
            else{
                klucze[size] = klucz;
                wartosci[size] = wartosc;
            }
            size++;
        }
        public void Remove(K klucz){
            bool usunieto = false;
            for(int i = 0; i < (size-1); i++){
                if(usunieto == true){
                    klucze[i] = klucze[i+1];
                    wartosci[i] = wartosci[i+1];
                }
                else if(Equals(klucze[i], klucz)){
                    usunieto = true;
                    klucze[i] = klucze[i+1];
                    wartosci[i] = wartosci[i+1];
                }
                else if((i == size - 1) || (Equals(klucze[i], klucz))){
                    Array.Resize(ref klucze, size-1);
                    Array.Resize(ref wartosci, size-1);
                }
            }
            size--;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Slownik<string, int> testowy = new Slownik<string, int>();
            testowy.Add("a",0);
            Console.WriteLine(testowy.search("a"));
            Console.WriteLine(testowy.get_size());
            testowy.Add("b",1);
            testowy.Add("c",2);
            testowy.Add("d",3);
            Console.WriteLine(testowy.search("b"));
            Console.WriteLine(testowy.get_size());
            testowy.Remove("b");
            Console.WriteLine(testowy.search("c"));
            Console.WriteLine(testowy.get_size());
            testowy.Remove("d");
            Console.WriteLine(testowy.get_size());
        }
    }
}
