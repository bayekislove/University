public class zad2 {
    public static void main(String[] args){
        wyrazenie k = new Stala(4);
        wyrazenie x = new Zmienna("x", 3);
        wyrazenie s = new Add(k, x);
        System.out.println(s.getstring());
        System.out.println(s.oblicz());
        x = new Zmienna("x", 8);
        System.out.println(x.getstring());
        System.out.println(x.oblicz());
        System.out.println(s.getstring());
        System.out.println(s.oblicz());
        s = new Div(x, k);
        System.out.println(s.getstring());
        System.out.println(s.oblicz());
        wyrazenie p = new Sub(new Stala(7), new Stala(-3));
        wyrazenie a = new Mult(new Stala(7), new Stala(5));
        System.out.println(a.getstring());
        System.out.println(a.oblicz());
        System.out.println(p.getstring());
        System.out.println(p.oblicz());
        System.out.println((new Div(new Stala(3), new Stala(0))).getstring()); 
        System.out.println((new Div(new Stala(3), new Stala(0))).oblicz()); // no a tutaj wywala blad
    }
}