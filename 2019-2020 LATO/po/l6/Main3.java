public class Main3{
    public static void main(String[] args){
        bufor<String> testowy = new bufor<String>(20);
        producent kamil = new producent(testowy);
        konsument andrzej = new konsument(testowy);
        kamil.start();
        andrzej.start();
    }
}