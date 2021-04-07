public class Punkt {
    private double x;
    private double y;

    Punkt(double px, double py){
        x = px; y = py;
    }

    public boolean equals(Punkt p){
        return p.x == this.x && p.y == this.y;
    }

    public double getX(){
        return this.x;
    }

    public double getY(){
        return this.y;
    }

    public void przesun(Wektor w){
        x += w.dx;
        y += w.dy;
    }

    public void obroc(Punkt p, double kat){
        x = Math.cos(kat) * (x - p.x) - Math.sin(kat) * (y - p.y) + p.x;
        y = Math.sin(kat) * (x - p.x) + Math.cos(kat) * (y - p.y) + p.y;
    }

    public void odbij(Prosta p){
        Prosta k;
        if(p.getA() == 0)
            k = new Prosta(1.0, 0.0, p.getC());
        else if(p.getB() == 0)
            k = new Prosta(0.0, -1.0, p.getC());
        else
            k = new Prosta((-1.0)/p.getA(), p.getB(), this.y + (-1.0)/p.getA()*this.x);

        Punkt przeciecie = Prosta.punkt_przeciecia(k, p);

        Wektor do_przeciecia = new Wektor(przeciecie.x - this.x, przeciecie.y - this.y);
        this.x = przeciecie.x + do_przeciecia.dx;
        this.y = przeciecie.y + do_przeciecia.dy;

    }

    public void wydrukuj(){
        System.out.println("(" + String.valueOf(x) + ", " + String.valueOf(y) + ")");
    }
}
