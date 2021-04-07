package obliczenia;

public class Maximum extends Operator2arg{
    public Maximum(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        return Math.max(left.oblicz(), right.oblicz());
    }

    @Override
    public String toString(){
        return "max((" + left.toString() + "),(" + right.toString() + "))";
    }
}