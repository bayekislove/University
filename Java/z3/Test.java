import struktury.*;

public class Test {
    public static void main(String[] args) throws Exception{
        Para pies = new Para("pies", 1);
        Para zolw = new Para("zolw", 1);
        Para kot = new Para("kot", 2);
        Para zolw2 = new Para("zolw", 2);
        ZbiorNaTablicy zbior = new ZbiorNaTablicy(2);
        zbior.insert(kot);
        zbior.insert(pies);
        System.out.println(zbior.search("kot"));    //wypisz kota
        zbior.delete("kot");
        zbior.insert(zolw);
        System.out.println(zbior.read("zolw"));   //wartosc zolwia
        zbior.set(zolw2);
        System.out.println(zbior.read("zolw"));   //wartosc zolwia po zmianie
        System.out.println(zbior.how_many());            //how_many elementow
        zbior.clean();
        System.out.println(zbior.how_many());            //how_many elementow po czyszczeniu

        ZbiorNaTablicyDynamicznej zbior2 = new ZbiorNaTablicyDynamicznej();
        zbior2.insert(pies);
        zbior2.insert(kot);
        zbior2.insert(zolw);
        System.out.println(zbior2.search("zolw"));
         
        ZbiorNaTablicy znt = new ZbiorNaTablicy(3);
        znt.insert(new Para(new String("jeden"), 1.0));
        System.out.println(znt.how_many());
        System.out.println(znt.read("jeden"));
        znt.set(new Para(new String("jeden"), 10.0));
        System.out.println(znt.read("jeden"));
        znt.delete("jeden");
        try 
        {
            znt.search("jeden");
        }
        catch(Exception e)
        {
            System.out.print("Nie ma tego w słowniku, bo jest usunięte w linijce ");
        }


        ZbiorNaTablicyDynamicznej zntd = new ZbiorNaTablicyDynamicznej();
        System.out.println(zntd.how_many());
        zntd.insert(new Para(new String("jeden"), 1.0));
        zntd.insert(new Para(new String("dwa"), 2.0));
        zntd.insert(new Para(new String("trzy"), 3.0));
        System.out.println(zntd.how_many());
    }    
}
