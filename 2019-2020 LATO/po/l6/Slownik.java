import java.io.*;
import java.util.ArrayList;
import java.util.List;
public class Slownik<K,V> implements Serializable{
    private List<K> klucze;
    private List<V> wartosci;
    private static final long serialVersionUID = 1;
    public Slownik(){
        klucze = new ArrayList<K>();
        wartosci = new ArrayList<V>();
    }
    
    public int get_size(){
        return klucze.size();
    }

    public void Add(K klucz, V wartosc){
        klucze.add(klucz);
        wartosci.add(wartosc);
    }

    public void Remove(K klucz){
        int pom = klucze.indexOf(klucz);
        klucze.remove(pom);
        wartosci.remove(pom);
    }

    public V FindVal(K klucz){
        return wartosci.get(klucze.indexOf(klucz));
    }
}