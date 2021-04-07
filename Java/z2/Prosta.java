public class Prosta { //Ax+By+C
    private double a;
    private double b;
    private double c;

    Prosta(Punkt ap, Punkt bp){
        if(ap.getX() - bp.getX() == 0){
            a = -1.0;
            b = 0.0;
            c = ap.getX();
        }
        else if(ap.getY() - bp.getY() == 0){
            a = 0.0;
            b = -1.0;
            c = ap.getY();
        }
        else{
            a = (ap.getY() - bp.getY()) / (ap.getX() - bp.getX());
            b = -1.0;
            c = (ap.getY() - a * ap.getX());
        }
    }

    Prosta(double ax, double bx, double cx){
        this.a = ax; this.b = bx; this.c = cx;
    }

    public boolean equals(Prosta l){
        return l.a == a && l.b == b && l.c == c;
    }

    public boolean lezy(Punkt p){
        return a * p.getX() + b * p.getY() + c == 0;
    }

    public void przesun(Wektor w){
        this.c += w.dy - a * w.dx;
    }

    public void wydrukuj(){
        if(b != 0)
            System.out.println("y = " + String.valueOf(a) + "x + " + String.valueOf(c));
        else
            System.out.println("x = " + String.valueOf(c));
    }

    public double getA(){ return a; };
    public double getB(){ return b; };
    public double getC(){ return c; };

    public static boolean czy_rownolegle(Prosta k, Prosta m){
        if( k.getA() == -1 && k.getB() == 0 &&
            m.getA() == -1 && m.getB() == 0)
            return true;
        if( k.getA() == 0 && k.getB() == -1.0 &&
            m.getA() == 0 && m.getB() == -1.0)
            return true;
        return k.getA() == m.getA();
    }

    public static boolean czy_prostopadle(Prosta k, Prosta m){
        if( k.getA() == 0.0 && m.getB() == -1.0 ||
            k.getA() == -1.0 && m.getB() == 0.0)
                return true;
        return k.getA()*m.getA() == -1.0;
    }

    public static Punkt punkt_przeciecia(Prosta k, Prosta m){
        if(Prosta.czy_rownolegle(k, m))
            throw new IllegalArgumentException("Te proste są równoległe!");
        double x_prz = (k.getC() - m.getC())/(m.getA() - k.getA());
        return new Punkt( x_prz, k.getA()*x_prz + k.getC() );
    }
}
