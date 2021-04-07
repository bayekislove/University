using System;

namespace nowy
{
    class Wektor{
        private float[] wspolrzedne;
        private int wymiar;
        public Wektor(float[] inicjator){
            wspolrzedne = inicjator;
            wymiar = wspolrzedne.Length;
        }
        public float ZwrocReprezentacje(int i){
            return this.wspolrzedne[i-1];
        }
        public int SprawdzWymiar(){
            return this.wymiar;
        }
        public void DodajWektor(Wektor w){
            if(this.wymiar <= w.SprawdzWymiar()){
                Array.Resize(ref this.wspolrzedne, w.SprawdzWymiar());
                for(int i = 0; i < this.wymiar; i++){
                    this.wspolrzedne[i] += w.wspolrzedne[i]; 
                }
                for(int i = this.wymiar; i < w.SprawdzWymiar(); i++){
                    this.wspolrzedne[i] = w.wspolrzedne[i];
                }
                this.wymiar = wspolrzedne.Length;
            } 
            else{
                for(int i = 0; i < w.SprawdzWymiar(); i++){
                    this.wspolrzedne[i] += w.wspolrzedne[i]; 
                }
            }
        }
        public void Pomnoz(float k){
            for(int i = 0; i < this.wymiar; i++){
                this.wspolrzedne[i] *= k;
            }
        }
        public float Pomnoz(Wektor inp){
            float suma = 0;
            if(this.wymiar <= inp.SprawdzWymiar()){
                for(int i = 0; i < this.wymiar; i++){
                    suma += this.wspolrzedne[i] * inp.wspolrzedne[i];
                }
            }
            else{
                for(int i = 0; i < inp.SprawdzWymiar(); i++){
                    suma += this.wspolrzedne[i] * inp.wspolrzedne[i];
                }
            }
            return suma;
        }
        public class Macierz{
            private Wektor[] wiersze;
            private int lkolumn;
            private int lwierszy;
            public Macierz(Wektor[] input){
                bool matrix_possible = true;
                for(int i = 0; i < input.Length - 1; i++){
                    if(input[i].SprawdzWymiar() != input[i+1].SprawdzWymiar()){
                        matrix_possible = false;
                        break;
                    }
                }
                if(matrix_possible == true){
                    wiersze = input;
                    lwierszy = wiersze.Length;
                    lkolumn = wiersze[0].SprawdzWymiar();
                } 
            }
            public int ZwrocWymiar(){
                return this.lwierszy;
            }
            public Wektor ZwrocWiersz(int i){
                return this.wiersze[i];
            }
            public void DodajMacierz(Macierz inp){
                if((inp.lkolumn != this.lkolumn) || (inp.lwierszy != this.lwierszy)){
                    Console.WriteLine("Dodawanie niemożliwe, błędne parametry");
                }
                else{
                    for(int i = 0; i < this.lwierszy; i++){
                        this.wiersze[i].DodajWektor(inp.ZwrocWiersz(i));
                    }
                }
            }
            public Wektor Przemnoz(Wektor inp){
                if(this.lwierszy != inp.wymiar){
                    return default(Wektor); 
                }
                float[] pom = new float[inp.wymiar];
                for(int i = 0; i < inp.wymiar; i++){
                    float suma = 0;
                    for(int k = 0; k < inp.wymiar; k++){
                        suma += (this.ZwrocWiersz(i)).ZwrocReprezentacje(k+1) * inp.ZwrocReprezentacje(k+1); //to wynika z niusansu w implementacji
                    }                                                                                         //funckji ZwrocReprezentacje
                    pom[i] = suma;
                }
                Wektor zwrot = new Wektor(pom);
                return zwrot;
            }
            public Wektor.Macierz Przemnoz(Macierz inp){
                if(this.lkolumn != inp.lwierszy){
                    Console.WriteLine("Invalid input");
                    return default(Wektor.Macierz);
                }
                Wektor[] scratch = new Wektor[this.lwierszy];
                for(int i = 0; i < this.lwierszy; i++){
                    float[] nowy_wiersz = new float[this.lkolumn];
                    for(int k = 0; k < this.lkolumn; k++){
                        for(int j=0; j<inp.lwierszy; j++){
                            nowy_wiersz[k] += (this.ZwrocWiersz(i)).ZwrocReprezentacje(j+1) * (inp.ZwrocWiersz(j)).ZwrocReprezentacje(k+1);
                        }
                    }
                    Wektor pom = new Wektor(nowy_wiersz);
                    scratch[i] = pom;
                }
                Wektor.Macierz temp = new Wektor.Macierz(scratch);
                return temp;
            }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Wektor testowy = new Wektor(new float[2] {1, 3});
            Wektor testowy2 = new Wektor(new float[4] {1,3,5,6});
            testowy.DodajWektor(testowy2);
            testowy.Pomnoz(5);
            Console.WriteLine(testowy.ZwrocReprezentacje(4)); 
            Console.WriteLine(testowy.Pomnoz(testowy2));
            Console.WriteLine("Drukuję kolejne współrzędne wektora testowego");
            for(int i = 1; i <= testowy.SprawdzWymiar(); i++){
                Console.WriteLine(testowy.ZwrocReprezentacje(i));
            }
            Wektor skladowa1 = new Wektor(new float[3] {9, 8, 0});
            Wektor skladowa2 = new Wektor(new float[3] {9, 8, 1});
            Wektor skladowa3 = new Wektor(new float[3] {1, 1, 1});
            Wektor skladowa4 = new Wektor(new float[3] {4, 3, 2});
            Wektor[] macierz_comp = new Wektor[3]{skladowa1, skladowa2, skladowa3};
            Wektor.Macierz matrix = new Wektor.Macierz(macierz_comp);
            Wektor mnozenie_wekt = matrix.Przemnoz(skladowa4);
            Console.WriteLine("Drukuję kolejne współrzędne z wymnożenia macierzy przez wektor");
            for(int i = 1; i <= mnozenie_wekt.SprawdzWymiar(); i++){
                Console.WriteLine(mnozenie_wekt.ZwrocReprezentacje(i));
            }
            Wektor pom1 = new Wektor(new float[3] {2, 1, 3});
            Wektor pom2 = new Wektor(new float[3] {-1, 4, 0});
            Wektor[] asda = new Wektor[2]{pom1, pom2};
            Wektor.Macierz pierwsza = new Wektor.Macierz(asda);
            Wektor temp1 = new Wektor(new float[3] {1, 3, 2});
            Wektor temp2 = new Wektor(new float[3] {-2, 0, 1});
            Wektor temp3 = new Wektor(new float[3] {5, -3, 2});
            Wektor[] dada = new Wektor[3]{temp1, temp2, temp3};
            Wektor.Macierz druga = new Wektor.Macierz(dada);
            Wektor.Macierz trzecia = pierwsza.Przemnoz(druga);
            Console.WriteLine("Wypisywanie elementów macierzy pierw x drug");
            for(int i = 0; i < trzecia.ZwrocWymiar(); i++){
                Console.WriteLine("Wypisuję wiersz {0}:", i+1);
                for(int k = 0; k < (trzecia.ZwrocWiersz(i)).SprawdzWymiar(); k++){
                    Console.WriteLine(trzecia.ZwrocWiersz(i).ZwrocReprezentacje(k+1));
                }
            }
        }
    }
}
