import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;

public class Okno implements ActionListener {
    String argss[];
    JTextField nazwisko_autora; 
    JTextField rok_wydania; 
    JTextField zniszczona;
    JTextField kolor;
    JTextField oceny;
    JTextField imie_autora; 
    JTextField tytul;
    JFrame frame = new JFrame("Ksiazka");
    public Okno(String args[]) {
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container kontener = frame.getContentPane();
        GridLayout layout;

        if(args[0].equals("Ksiazka")){
            layout = new GridLayout(4, 2);
        }
        else{
            layout = new GridLayout(6, 2);
        }

        kontener.setLayout(layout);
        JLabel nazwisko_autora_etykieta = new JLabel("nazwisko_autora");
        kontener.add(nazwisko_autora_etykieta);
        nazwisko_autora = new JTextField("", 50);
        kontener.add(nazwisko_autora);
        JLabel rok_wydania_etykieta = new JLabel("rok_wydania");
        kontener.add(rok_wydania_etykieta);
        rok_wydania = new JTextField("", 50);
        kontener.add(rok_wydania);
        JLabel kolor_etykieta = new JLabel("kolor");
        kontener.add(kolor_etykieta);
        kolor = new JTextField("", 50);
        kontener.add(kolor);

        if(args[0].equals("Ksiazka")){
            //juz wszystko jest za nas ustawione wyzej
        }

        else{
            if(args[0].equals("Bestseller")){
                JLabel imie_autora_etykieta = new JLabel("imie_autora");
                kontener.add(imie_autora_etykieta);
                imie_autora = new JTextField("", 45);
                kontener.add(imie_autora);
                JLabel tytul_etykieta = new JLabel("tytul");
                kontener.add(tytul_etykieta);
                zniszczona = new JTextField("", 45);
                kontener.add(tytul);
            }
        else{
                JLabel oceny_etykieta = new JLabel("siedzenia");
                kontener.add(oceny_etykieta);
                oceny = new JTextField("", 45);
                kontener.add(oceny);
                JLabel zniszczona_etykieta = new JLabel("wagony");
                kontener.add(zniszczona_etykieta);
                zniszczona = new JTextField("", 45);
                kontener.add(zniszczona);
            }
        }
        JButton save = new JButton("Zapisz");
        save.addActionListener(this);
        kontener.add(save);
        JButton write = new JButton("Wypisz");
        write.addActionListener(new Listner(args, kolor, rok_wydania, nazwisko_autora, imie_autora, tytul, frame));
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new Okno(args);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (argss[0].equals("Ksiazka")) {
            Ksiazka pom = new Ksiazka(kolor.getText(), Integer.parseInt(rok_wydania.getText()), nazwisko_autora.getText());
            try {
                pom.pisz(this.argss);
            } 
            catch (IOException e1) {
                e1.printStackTrace();
            }
        }
        if (argss[0].equals("Bestseller")){
                Bestseller pom = new Bestseller(kolor.getText(), nazwisko_autora.getText(), Integer.parseInt(rok_wydania.getText()),
                tytul.getText(), imie_autora.getText());
            try {
                pom.pisz(this.argss);
            }
            catch (IOException e1) {
                // TODO Auto-generated catch block
                e1.printStackTrace();
            }
        }
        else{
            Czasopismo pom = new Czasopismo(kolor.getText(), nazwisko_autora.getText(), Integer.parseInt(rok_wydania.getText()),
            Integer.parseInt(oceny.getText()), Boolean.parseBoolean(zniszczona.getText()));
            try {
                pom.pisz(argss);
            } catch (IOException e1) {
                // TODO Auto-generated catch block
                e1.printStackTrace();
            }
    }
}
}
