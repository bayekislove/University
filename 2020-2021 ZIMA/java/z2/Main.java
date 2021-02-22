public class Main{
    public static void main(String args[]){  
        Prosta k = (new Prosta((new Punkt(3, 3)), (new Punkt(2, 2))));
        Prosta p = (new Prosta((new Punkt(2, 6)), (new Punkt(1, 2))));
        Prosta s = (new Prosta((new Punkt(1, 1)), (new Punkt(2, 1))));

        System.out.println(Prosta.czy_rownolegle(k, p));
        k.wydrukuj();
        p.wydrukuj();
        s.wydrukuj();

        System.out.println("Start punktów przecięcia");
        (Prosta.punkt_przeciecia(k, p)).wydrukuj();
        (Prosta.punkt_przeciecia(k, s)).wydrukuj();
        (Prosta.punkt_przeciecia(p, s)).wydrukuj();
        System.out.println("Koniec punktów przecięcia");
        
        Punkt p1 = new Punkt(1,1);
        Wektor w1 = new Wektor(3,3);
        p1.przesun(w1);
        p1.wydrukuj();

        Punkt p2 = new Punkt(0, 1);
        p2.odbij(k);
        p2.wydrukuj();
    }
}