package obliczenia;

public class Mniejsze extends Operator2arg{
    public Mniejsze(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        return left.oblicz() < right.oblicz() ? 1.0 : 0.0;
    }

    @Override
    public String toString(){
        return "(" + left.toString() + ") < (" + right.toString() + ")";
    }
}
