public class Stala extends wyrazenie{
    int wartosc;
    Stala(int constant){
        wartosc = constant;
    }
    public int oblicz(){
        return wartosc;
    }
    public String getstring(){
        return String.valueOf(wartosc);
    }
}