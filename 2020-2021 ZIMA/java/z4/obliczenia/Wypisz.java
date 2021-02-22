package obliczenia;

public class Wypisz extends Instrukcja {
    Wyrazenie l;

    public Wypisz(Wyrazenie inp){
        l =  inp;
    }

    @Override
    public void wykonaj(){
        System.out.println(l.oblicz());
    }
}
