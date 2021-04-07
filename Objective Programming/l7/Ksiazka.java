import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class Ksiazka implements Serializable{
    private static final long serialVersionUID = 1L;
    String kolor;
    int rok_wydania;
    String nazwisko_autora;
    @Override
    public String toString() {
        return kolor + " " + rok_wydania + " "+ nazwisko_autora;
    }
    public Ksiazka(String kolor,int rok_wydania,String nazwisko_autora){
        this.kolor=kolor;
        this.rok_wydania=rok_wydania;
        this.nazwisko_autora=nazwisko_autora;
    }
    public void pisz(String[] args) throws FileNotFoundException, IOException {
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(args[1]))) {
        out.writeObject(this);
        }
    }
    public static Ksiazka czytaj(String[] args) throws FileNotFoundException, IOException, ClassNotFoundException {
        try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(args[1]))) {
            Ksiazka temp = (Ksiazka) inputStream.readObject();
            return temp;
        }
    }
}