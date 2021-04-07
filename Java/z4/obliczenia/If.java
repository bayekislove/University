package obliczenia;

public class If extends Instrukcja{
    Wyrazenie warunkowe;
    Instrukcja T;

    public If(Wyrazenie iff, Instrukcja ts){
        if(ts == null)
            throw new IllegalArgumentException();
        warunkowe = iff; T = ts;
    }

    @Override
    public void wykonaj() throws Exception {
        if(warunkowe.oblicz() != 0){
            T.wykonaj();
        }
    }
}
