package obliczenia;
import java.util.*;

public class Czytaj extends Instrukcja{
    double a;
    String name;

    public Czytaj(String ref){
        Scanner inp = new Scanner(System.in);
        a = inp.nextInt();
        name = ref;
        inp.close();
    }

    @Override
    public void wykonaj(){
        Zmienna.Przypisz(name, a);
    }
}
