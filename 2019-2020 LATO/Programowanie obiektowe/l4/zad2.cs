using System;
using System.Collections.Generic;

namespace l4
{
    class PrimeCollection : IEnumerable{
        int position;
        public IEnumerator GetEnumerator(){
            return new PrimeCollectionEnumerator();
        }
    }
    class PrimeCollectionEnumerator : IEnumerator{
        private bool in_range = true;
        private int position;
        private int iterator;
        const int max_rozmiar = 2147483647;
        public PrimeCollectionEnumerator(){
            this.position = 2;
            this.iterator = 2;
        }
        private bool is_prime(int number){
            if(number == 0 || number == 1){ 
                return false;
                }
            for(int i = 2; i < Math.Sqrt(number); i++){
                if(number % i == 0){
                    return false;
                }
            }   
            return true;
        }
        public bool MoveNext(){
            if(in_range == false){
                return false;
            }
            iterator++;
            while(iterator < max_rozmiar !&& is_prime(iterator) == true){
                iterator++;
            }
            if(iterator!=max_rozmiar){
                position = iterator;
            }
            else{
                in_range = false;
            }
            return iterator!=max_rozmiar;
        }
        public object Current{ get { return position; } }
        public void Reset(){
            position = 2;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            //PrimeCollection test = new PrimeCollection();
            //foreach(int el in test)
              //  Console.WriteLine(el);
            List<int>[] cos = new List<int>[64];
            cos[0].Add((int)1);
            Console.WriteLine(cos[0][0]);
        }
    }
}
