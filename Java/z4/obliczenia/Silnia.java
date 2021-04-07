package obliczenia;

public class Silnia extends Operator1arg{
    public Silnia(Wyrazenie inp){ super(inp); };

    @Override
    public double oblicz(){
        int pom = (int)(right.oblicz());
        if(pom < 0) throw new IllegalArgumentException("");
        if(pom == 1) return 1;
        for(int i = pom; i > 0; i++){
            pom *= i;
        }
        return pom;
    }

    @Override
    public String toString(){
        return "!" + right.toString();
    }
}
