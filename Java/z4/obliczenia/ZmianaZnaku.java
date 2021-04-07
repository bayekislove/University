package obliczenia;

public class ZmianaZnaku extends Operator1arg{
    public ZmianaZnaku(Wyrazenie inp){
        super(inp);
    }

    @Override
    public double oblicz(){
        return -(right.oblicz());
    }

    @Override
    public String toString(){
        return right.toString().charAt(0) == '-' ? right.toString().substring(0) : "-" + right.toString();
    }
}
