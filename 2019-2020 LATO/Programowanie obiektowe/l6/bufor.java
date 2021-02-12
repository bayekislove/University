import java.util.*;
public class bufor<T>{
    int max;
    private List<T> elementy;
    bufor(int input){
        max = input;
        elementy = new ArrayList<T>();
    }
    public synchronized void wloz(T elem) throws InterruptedException{ //metoda wait wymaga tego wyjatku
        while(elementy.size() == max){
            wait();
        }
        elementy.add(elem);
        notify();
    }

    public synchronized T zdejmij() throws InterruptedException{
        while(elementy.size() == 0){
            wait();
        }
        notify();
        return elementy.remove(0);
    }
}
