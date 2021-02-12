import java.util.Random;

public class producent extends Thread{
    bufor<String> buforek;
    producent(bufor<String> inp){
        buforek = inp;
    }
    @Override
    public void run(){ //nadpisujemy metode klasy Thread
        while(true){
            Random rands = new Random();
            try{
                System.out.println("Nowy element");
                buforek.wloz(Integer.toString(rands.nextInt(854)));
            }
            catch(InterruptedException exception){
                System.out.println("Producenckie opps");
            }
        }
    }
}