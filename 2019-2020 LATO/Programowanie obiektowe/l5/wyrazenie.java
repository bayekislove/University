import java.util.Hashtable;
abstract public class wyrazenie{
    static Hashtable<String, Integer> przechowalnia = new Hashtable<String,Integer>();
    abstract public String getstring();
    abstract public int oblicz();
}
