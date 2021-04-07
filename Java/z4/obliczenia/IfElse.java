package obliczenia;

public class IfElse extends Instrukcja{
    Wyrazenie warunkowe;
    Instrukcja T;
    Instrukcja F;

    public IfElse(Wyrazenie iff, Instrukcja ts, Instrukcja fs){
        if(ts == null)
            throw new IllegalArgumentException();
        warunkowe = iff; T = ts; F = fs;
    }

    @Override
    public void wykonaj() throws Exception {
        if(warunkowe.oblicz() != 0)
            T.wykonaj();
        else
            F.wykonaj();
    }
}