package obliczenia;

public class While extends Instrukcja{
    Wyrazenie TF;
    Blok body;

    public While(Wyrazenie inp, Blok i){
        if(inp == null || i == null)
            throw new IllegalArgumentException();
        TF = inp; body = i;
    }

    @Override
    public void wykonaj() throws Exception {
        while(TF.oblicz() != 0.0){
            body.wykonaj();
        }
    }
}
