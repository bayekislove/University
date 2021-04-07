package obliczenia;
import java.util.Hashtable;

public class Zmienna extends Wyrazenie{
    static final Hashtable<String, Double> set = new Hashtable<String, Double>();
    String name;

    public Zmienna(String name, Double val){
        if(set.containsKey(name))
            set.replace(name, val);
        else
            set.put(name, val);
        this.name = name;
    };

    public Zmienna(String name){
        this.name = name;
        if(!set.containsKey(name))
            set.put(name, 0.0);        
    };

    public int zadeklarowane_zmienne(){ return set.size(); }

    public double oblicz(){
        return set.get(name);
    }

    public static boolean jest(String name){
        return set.contains(name);
    }

    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof Zmienna)) return false;
        return this.name == ((Zmienna)obj).name;
    }

    @Override
    public String toString(){
        return name;
    }

    public void PrzypiszZm(Double val){
        set.replace(this.name, val);
    }

    public static void Przypisz(String name, Double val){
        if(set.containsKey(name))
            set.replace(name, val);
        else
            throw new IllegalArgumentException("Wybierz zmienną która już jest zainicjalizowana!");
    }

    public static void Zwolnij(String name){
        try
        {
            set.remove(name);
        }
        catch(Exception e){ }
    }
}
