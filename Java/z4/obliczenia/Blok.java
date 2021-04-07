package obliczenia;

import java.util.Vector;

public class Blok extends Instrukcja{
    Instrukcja[] doZrobienia;
    private Vector<String> zmienne;

    public Blok(Instrukcja... instrukcjas){
        doZrobienia = instrukcjas;
        zmienne = new Vector<String>();
    }

    public void wykonaj() throws Exception {
        for (Instrukcja ins : doZrobienia){
            if(ins instanceof ZmDekl){
                if(Zmienna.jest(((ZmDekl)ins).getName()))
                    throw new Exception("Zmienna już jest zadeklarowana");
                else
                    zmienne.add(((ZmDekl)ins).getName());
            }
            ins.wykonaj();
        }

        for (String wywalic : zmienne){
            Zmienna.Zwolnij(wywalic);
        }
    }
}