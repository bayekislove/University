import java.awt.event.*;
import java.io.IOException;
import javax.swing.JFrame;
import javax.swing.JTextField;

public class Listner implements ActionListener {
    JFrame frame;
    String argss[];
    JTextField kolor; 
    JTextField rok_wydania; 
    JTextField nazwisko_autora; 
    JTextField zniszczona;
    JTextField oceny;
    JTextField tytul;
    JTextField imie_autora; 
    Listner(String args[], JTextField kolor,JTextField rok_wydania,JTextField nazwisko_autora,
    JTextField imie_autora,JTextField tytul,JFrame frame) {
        this.frame=frame;
        argss = args;
        this.kolor=kolor;
        this.rok_wydania=rok_wydania;
        this.nazwisko_autora=nazwisko_autora;
        this.imie_autora=imie_autora;
        this.tytul=tytul;
    }
    public void nadpiszp(Ksiazka p){
        nazwisko_autora.setText(String.valueOf(p.nazwisko_autora));
        kolor.setText(String.valueOf(p.kolor));
        rok_wydania.setText(String.valueOf(p.rok_wydania));
        this.frame.setVisible(true);
    }
    public void nadpiszb(Bestseller p){
        nazwisko_autora.setText(String.valueOf(p.nazwisko_autora));
        kolor.setText(String.valueOf(p.kolor));
        rok_wydania.setText(String.valueOf(p.rok_wydania));
        imie_autora.setText(String.valueOf(p.imie_autora));;
        tytul.setText(String.valueOf(p.tytul));;
        this.frame.setVisible(true);
    }
    public void nadpiszcz(Czasopismo p){
        nazwisko_autora.setText(String.valueOf(p.nazwisko_autora));
        kolor.setText(String.valueOf(p.kolor));
        rok_wydania.setText(String.valueOf(p.rok_wydania));
        zniszczona.setText(String.valueOf(p.zniszczona));;
        oceny.setText(String.valueOf(p.oceny));;
        this.frame.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (argss[0].equals("Ksiazka")) {
            Ksiazka p;
            try {
                p = Ksiazka.czytaj(argss);
            } catch (ClassNotFoundException | IOException e1) {
                p=new Ksiazka("",0,"");
                try {
                    p.pisz(argss);
                } catch (IOException e2) {
                    // TODO Auto-generated catch block
                }
            }
            this.nadpiszp(p);

        } else {
            if (argss[0].equals("Bestseller")) {
                Bestseller p;
                try {
                    p = Bestseller.czytaj(argss);
                } catch (ClassNotFoundException | IOException e1) {
                    // TODO Auto-generated catch block
                    p= new Bestseller("","", 0, "", "");
                } 
                this.nadpiszb(p);
            } else {
                Czasopismo p;
                try {
                    p = Czasopismo.czytaj(argss);
                } catch (ClassNotFoundException | IOException e1) {
                    // TODO Auto-generated catch block
                    p= new Czasopismo("", "", 0, 0, false);
                }
                this.nadpiszcz(p);
        }
    }
}

}