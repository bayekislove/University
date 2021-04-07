package obliczenia;

public class ZmDekl extends Instrukcja{
    final String name;

    public String getName(){
        return name;
    }

    public ZmDekl(String n){
        name = n;
    }

    @Override
    public void wykonaj(){
        new Zmienna(name, 0.0);
    }
}
