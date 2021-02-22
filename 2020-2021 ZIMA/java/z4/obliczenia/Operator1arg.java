package obliczenia;

public abstract class Operator1arg extends Wyrazenie{
    Wyrazenie right;

    Operator1arg(Wyrazenie op){
        right = op;
    }
}
