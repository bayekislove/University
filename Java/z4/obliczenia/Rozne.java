package obliczenia;

public class Rozne extends Operator2arg{
    public Rozne(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        return left.oblicz() == right.oblicz() ? 0.0 : 1.0;
    }

    @Override
    public String toString(){
        return "(" + left.toString() + ") != (" + right.toString() + ")";
    }
}
