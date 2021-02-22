public class Odcinek {
    Punkt start;
    Punkt koniec;

    Odcinek(Punkt sstart, Punkt kkoniec){
        if(sstart.equals(kkoniec)) throw new IllegalArgumentException("Insert points that are not equal!");
        start = sstart; koniec = kkoniec;
    }

    public void przesun(Wektor w){
        start.przesun(w);
        koniec.przesun(w);
    }

    public void obroc(Punkt p, double kat){
        start.obroc(p, kat);
        koniec.obroc(p, kat);
    }
}