package obliczenia;

public class Minimum extends Operator2arg{
    public Minimum(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        return Math.min(left.oblicz(), right.oblicz());
    }

    @Override
    public String toString(){
        return "min((" + left.toString() + "),(" + right.toString() + "))";
    }
}