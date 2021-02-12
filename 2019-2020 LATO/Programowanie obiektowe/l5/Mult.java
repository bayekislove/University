public class Mult extends wyrazenie{
        wyrazenie lewa;
        wyrazenie prawa;
        Mult(wyrazenie lewe, wyrazenie prawe){
            lewa = lewe; prawa = prawe;
        }
        public int oblicz(){
            return lewa.oblicz() * prawa.oblicz();
        }
        public String getstring(){
            return "(" + lewa.getstring() + "*" + prawa.getstring() + ")";
        }
    }