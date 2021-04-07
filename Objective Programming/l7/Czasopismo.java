import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class Czasopismo extends Ksiazka {
    private static final long serialVersionUID = 3L;
    int oceny;
    boolean zniszczona;
    Czasopismo(String kolor,String nazwisko_autora,int rok_wydania,int oceny,boolean zniszczona){
        super(nazwisko_autora, rok_wydania, kolor);
        this.oceny=oceny;
        this.zniszczona=zniszczona;
    }
    public void pisz(String[] args) throws FileNotFoundException, IOException {
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(args[1]))) {
        out.writeObject(this);
        }
    }
    public static Czasopismo czytaj(String[] args) throws FileNotFoundException, IOException, ClassNotFoundException {
        try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(args[1]))) {
            Czasopismo temp = (Czasopismo) inputStream.readObject();
            return temp;
        }
    }
    @Override
    public String toString() {
        String temp="";
        if(zniszczona == true){
            temp="zniszczona";
        }else{
            temp="niezniszczona";
        }
        temp=rok_wydania+" "+oceny+" "+kolor+" "+nazwisko_autora+" "+temp;
        return temp;
    }
}