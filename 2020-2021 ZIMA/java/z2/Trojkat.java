public class Trojkat {
    Punkt a;
    Punkt b;
    Punkt c;

    Trojkat(Punkt pa, Punkt pb, Punkt pc){
        if((new Prosta(pa, pb).lezy(pc))) 
            throw new IllegalArgumentException("Te punkty są współliniowe!");

        a = pa;
        b = pb;
        c = pc;
    }

    public void przesun(Wektor w){
        a.przesun(w);
        b.przesun(w);
        c.przesun(w);
    }

    public void obroc(Punkt p, double kat){
        a.obroc(p, kat);
        b.obroc(p, kat);
        c.obroc(p, kat);
    }
}
