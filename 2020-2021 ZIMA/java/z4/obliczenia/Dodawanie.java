package obliczenia;

public class Dodawanie extends Operator2arg{
    public Dodawanie(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        return left.oblicz() + right.oblicz();
    }

    @Override
    public String toString(){
        return "(" + left.toString() + ")+(" + right.toString() + ")";
    }
}