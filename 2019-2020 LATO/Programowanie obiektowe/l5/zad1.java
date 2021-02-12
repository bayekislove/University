public class zad1{
    public static void main(String[] args) {
        aspirant antek = new aspirant();
        inspektor kamil = new inspektor();
        posterunkowy mietek = new posterunkowy();
        sierzant michal = new sierzant();
        System.out.println(mietek);
        rankcollection policja = new rankcollection();
        policja.rankadd(antek);
        policja.rankadd(mietek);
        policja.rankadd(michal);
        policja.rankadd(kamil);
        policja.rankprint();
        policja.rankremove();
        policja.rankremove();
        policja.rankprint();
        }
    }

