package obliczenia;

public class DoWhile extends Instrukcja{
    Wyrazenie TF;
    Instrukcja body;

    public DoWhile(Wyrazenie inp, Instrukcja i){
        if(inp == null || i == null)
            throw new IllegalArgumentException();
    }

    @Override
    public void wykonaj() throws Exception {
        body.wykonaj();
        if(TF.oblicz() == 0.0) return;
    }
}