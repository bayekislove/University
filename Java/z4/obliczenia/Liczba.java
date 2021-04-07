package obliczenia;

public class Liczba extends Wyrazenie{
    double val;
    
    public Liczba(double inp){ this.val = inp; };

    @Override
    public double oblicz() { return val; };

    @Override
    public boolean equals(Object inp){
        if(!(inp instanceof Liczba)) return false;
        return this.val == ((Liczba)inp).val;
    }

    @Override
    public String toString(){
        return val + "";
    }
}
