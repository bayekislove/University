import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import java.io.File;
public class Main1 {
    public static void main(String[] args) {
        Slownik<String, String> testowy = new Slownik<String, String>();
        testowy.Add("a", "1");
        testowy.Add("b", "2");
        File nowy = new File("asda.txt");
        FileOutputStream FoS = new FileOutputStream("asda.txt");
        ObjectOutputStream OoS = new ObjectOutputStream(FoS);
        OoS.writeObject(testowy);
        OoS.close();
        FileInputStream FiS = new FileInputStream("asda.txt");
        ObjectInputStream OiS = new ObjectInputStream(FiS);
        Slownik<String, String> pom = new Slownik<String, String>();
        pom = (Slownik<String,String>) OiS.readObject();
        OiS.close();
        System.out.println(pom.FindVal("a"));
    }
}