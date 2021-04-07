import obliczenia.*;

public class Main {
    public static void main(String[] args) throws Exception{
        Zmienna x = new Zmienna("x", 2.0);
        Wyrazenie w = new Dodawanie(
                                new Liczba(7),
                                new Mnozenie(
                                        x,
                                        new Liczba(5)));
        System.out.println(w.oblicz());
        System.out.println((new Dodawanie(new Liczba(3), new Liczba(5))).oblicz());
        System.out.println((new Mnozenie(new ZmianaZnaku(new Odejmowanie(new Liczba(2), x)), new Liczba(7))).oblicz());
        System.out.println((new Mnozenie(new ZmianaZnaku(new Odejmowanie(new Liczba(2), x)), new Liczba(7))).toString());
        System.out.println((new Mniejsze(new Dodawanie(new Potegowanie(new Liczba(2), new Liczba(5)), 
        new Mnozenie(new Liczba(2), x)), new Liczba(20))).oblicz());

        Instrukcja ins = new Blok(
            new ZmDekl("n"),
            new Czytaj("n"),
            new IfElse(new Mniejsze(new Zmienna("n") ,new Liczba(2)),new Wypisz(new Liczba(0)),
                new Blok(
                    new ZmDekl("p"),
                    new ZmiennaPrzyps("p",new Liczba(2)),
                    new ZmDekl("wyn"),
                    new While(new MniejszeRowne(new Mnozenie(new Zmienna("p"), new Zmienna("p")),new Zmienna("n")),
                        new Blok(
                            new If(new Rowne(new Modulo(new Zmienna("n"), new Zmienna("p")),new Liczba(0)),
                                new Blok(
                                    new ZmiennaPrzyps("wyn", new Zmienna("p")),
                                    new ZmiennaPrzyps("p",new Zmienna("n")))),
                                new ZmiennaPrzyps("p", new Dodawanie(new Zmienna("p"), new Liczba(1))))),
                                new IfElse(new Wieksze(new Zmienna("wyn"),new Liczba(0)), new Wypisz(new Liczba(0)),
                                new Wypisz(new Liczba(1))))));
                  ins.wykonaj();
    }
}
