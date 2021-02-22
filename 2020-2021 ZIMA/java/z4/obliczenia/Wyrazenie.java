package obliczenia;

public abstract class Wyrazenie implements Obliczalny{
    public static double suma(Wyrazenie... wyr)
    {
        double suma = 0;
        for(Wyrazenie pom : wyr){
            suma += pom.oblicz();
        }
        return suma;
    }

    public static double iloczyn(Wyrazenie... wyr)
    {
        double iloczyn = 1;
        for(Wyrazenie pom : wyr){
            iloczyn *= pom.oblicz();
        }
        return iloczyn;
    }
}
