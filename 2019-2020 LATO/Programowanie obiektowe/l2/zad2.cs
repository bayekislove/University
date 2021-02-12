using System;
namespace zad2
{
    class Array
    {
        Box start;
        Box end;
        Box last_searched;
        public int index_start;
        public int index_end;
        class Box{
            public int value;
            public int index;
            public Box next;
            public Box prev;
            public Box(){
                this.next = null;
                this.prev = null;
                this.value = 0; //0 jest tu tylko dlatego, ze nie moglem pozniej zamienic null na inta
                this.index = 0;
            }
        }
        public Array(int start, int end){
            this.index_start = start;
            this.index_end = end;
            this.start = new Box();
            this.start.index = start;
            this.last_searched = this.start;
            if(start > end){
                Console.WriteLine("Invalid index");
            }
            else if(start == end){
                this.end = this.start;
                this.start.index = start;
                this.end.index = start;
            }
            else{
                for(int i = index_start; i <= index_end; i++){
                    Box iterator = new Box();
                    iterator.index = i;
                    iterator.prev = last_searched;
                    last_searched.next = iterator;
                    last_searched = iterator;
                }
                this.end = last_searched;
            }
        }
        public int get(int searched_index){
            if(searched_index > this.index_end){
                Console.WriteLine("Value of highest index in array");
                return this.end.value;
            }
            if(searched_index < this.index_start){
                Console.WriteLine("Value of lowest index in array");
                return this.start.value;
            }
            if(searched_index <= this.last_searched.index){
                for(int i=this.last_searched.index; i > searched_index; i--){
                    last_searched = last_searched.prev;
                }
                return last_searched.value;
            }
            else{ //to znaczy ze indeks szukany bedzie wiekszy od temp indeksu
                for(int i=this.last_searched.index; i < searched_index; i++){
                    last_searched = last_searched.next;
                }
                return last_searched.value;
            }
        }
        public void set(int w_index, int w_value){ //funkcja ktora zmienia wartosc elementu w tablicy
            if(w_index > index_end){
                Array pomocnicza = new Array(index_end + 1, w_index);
                this.end.next = pomocnicza.start;
                pomocnicza.start.prev = this.end;
                this.end = pomocnicza.end;
                this.end.value = w_value;
                this.index_end = w_index;
            }
            if(w_index < index_start){
                Array pomocnicza = new Array(w_index, index_end - 1);
                this.start.prev = pomocnicza.end;
                pomocnicza.end.next = this.start.prev;
                this.start = pomocnicza.start;
                this.start.value = w_value;
                this.index_start = w_index;
            }
            if(w_index >= this.last_searched.index){
                for(int i=this.last_searched.index; i < w_index; i++){
                    last_searched = last_searched.next;
                }
                last_searched.value = w_value;
            }
            else{
                for(int i=this.last_searched.index; i > w_index; i--){
                    last_searched = last_searched.prev;
                }
                last_searched.value = w_value;
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Array tab = new Array(0,9);
            for(int i = 0; i <= 9; i++){
                tab.set(i,i);
                Console.WriteLine(tab.get(i));
            }
            tab.set(15, 15);
            Console.WriteLine(tab.get(13)); //bo ustawia wartosc 0 w pustych polach
            Console.WriteLine(tab.get(15));
        }
    }
}
