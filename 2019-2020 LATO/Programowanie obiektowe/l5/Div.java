public class Div extends wyrazenie{
    wyrazenie lewa;
    wyrazenie prawa;
    Div(wyrazenie lewe, wyrazenie prawe) throws ArithmeticException{
        lewa = lewe; prawa = prawe;
    }
    public int oblicz(){
        if(prawa.oblicz() == 0){
            throw new ArithmeticException("Enter right side which not evaluates to 0!");
        }
        return lewa.oblicz() / prawa.oblicz();
    }
    public String getstring(){
        return "(" + lewa.getstring() + "/" + prawa.getstring() + ")";
    }
}