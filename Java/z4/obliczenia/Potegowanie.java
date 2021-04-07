package obliczenia;

public class Potegowanie extends Operator2arg{
    public Potegowanie(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        return Math.pow(left.oblicz(), right.oblicz());
    }

    @Override
    public String toString(){
        return "(" + left.toString() + ")^(" + right.toString() + ")";
    }
}
