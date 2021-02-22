package obliczenia;

public class Dzielenie extends Operator2arg{
    public Dzielenie(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        if(right.oblicz() == 0.0) 
            throw new IllegalArgumentException("");
        return left.oblicz() / right.oblicz();
    }

    @Override
    public String toString(){
        return "(" + left.toString() + ")/(" + right.toString() + ")";
    }
}