package obliczenia;

public class ZmiennaPrzyps extends Instrukcja{
    String name;
    Wyrazenie val;

    public ZmiennaPrzyps(String s, Wyrazenie d){
        if(s == null || d == null)
            throw new IllegalArgumentException();
        name = s; val = d;
    }

    @Override
    public void wykonaj(){
        Zmienna.Przypisz(name, val.oblicz());
    }
}
