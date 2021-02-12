public class konsument extends Thread{
    bufor<String> buforek;
    konsument(bufor<String> inp){
        buforek = inp;
    }
    @Override
    public void run(){
        while(true){
            try{
                String k = buforek.zdejmij();
                System.out.println("Element usunieto: " + k + '\n');
            }
            catch(InterruptedException exception){
                System.out.println("Konsumencie oops");
            }
        }
    }
}