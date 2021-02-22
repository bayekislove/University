package obliczenia;

public abstract class Operator2arg extends Operator1arg{
    Wyrazenie left;

    Operator2arg(Wyrazenie l, Wyrazenie r){
        super(r); left = l;
    }
}
