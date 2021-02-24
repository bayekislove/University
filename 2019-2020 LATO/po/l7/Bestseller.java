import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class Bestseller extends Ksiazka {
    private static final long serialVersionUID = 2L;
    String tytul;
    String imie_autora;
    @Override
    public String toString() {
        return kolor + " " +  rok_wydania + " " + imie_autora + " " + nazwisko_autora + " " + tytul;
    }
    public Bestseller(String kolor, String nazwisko_autora, int rok_wydania, String tytul, String imie_autora) {
        super(nazwisko_autora, rok_wydania, kolor);
        this.rok_wydania = rok_wydania;
        this.tytul = tytul;
        this.imie_autora = imie_autora;
    }
    public static Bestseller czytaj(String[] args) throws FileNotFoundException, IOException, ClassNotFoundException {
        try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(args[1]))) {
            Bestseller temp = (Bestseller) inputStream.readObject();
            return temp;
        }
    }
    public void pisz(String[] args) throws FileNotFoundException, IOException {
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(args[1]))) {
        out.writeObject(this);
        }
    }
}