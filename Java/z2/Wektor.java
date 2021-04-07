public class Wektor {
    public final double dx;
    public final double dy;

    Wektor(double ddx, double ddy){
        dx = ddx; dy = ddy;
    }

    public static Wektor zloz(Wektor w, Wektor v){
        return new Wektor(w.dx + v.dx, w.dy + v.dy);
    }
}
