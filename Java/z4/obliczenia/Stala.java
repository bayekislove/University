package obliczenia;

public class Stala extends Wyrazenie{
    final String name;
    final double pi = Math.PI;
    final double e = Math.E;
    final double phi = 1.6180;

    public Stala(String inpName){
        if(!inpName.equals("π") || !inpName.equals("phi") || !inpName.equals("e"))
            throw new IllegalArgumentException("");
        name = inpName;
    }

    public double oblicz(){
        if(name.equals("π"))
            return pi;
        else if(name.equals("e"))
            return e;
        else
            return phi;
    }

    @Override
    public String toString(){
        return name;
    }
}
