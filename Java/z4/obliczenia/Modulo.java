package obliczenia;

public class Modulo extends Operator2arg{
    public Modulo(Wyrazenie l, Wyrazenie r){
        super(l, r);
    }

    @Override
    public double oblicz(){
        return (int)left.oblicz() % (int)right.oblicz();
    }

    @Override
    public String toString(){
        return "(" + left.toString() + ")%(" + right.toString() + ")";
    }
}