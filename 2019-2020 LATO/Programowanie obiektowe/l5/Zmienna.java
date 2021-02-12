public class Zmienna extends wyrazenie{
    private String nazwa;
    Zmienna(String identyfikator, int wartosc){ 
        przechowalnia.put(identyfikator, wartosc); 
        nazwa = identyfikator;
    }
    public int oblicz(){
        return przechowalnia.get(nazwa);
    }
    public String getstring(){
        return nazwa;
    }
    public void asda(){
        
    }
}