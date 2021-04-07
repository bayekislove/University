package obliczenia;

public class LogDyskretny extends Operator2arg{
    public LogDyskretny(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        return Math.log(left.oblicz())/ Math.log(right.oblicz());
    }

    @Override
    public String toString(){
        return "log((" + left.toString() + "), (" + right.toString() + "))";
    }
}