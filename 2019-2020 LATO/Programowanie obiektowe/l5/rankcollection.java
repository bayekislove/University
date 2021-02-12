import java.util.*;
public class rankcollection {
    List<rank> array;
    rankcollection(){
        this.array = new ArrayList<rank>(1);
    }
    void rankadd(rank input){
        int i = 0;
        boolean wstawiono = false;
        while(i != array.size()){
            if(input.get_rank() > array.get(i).get_rank()){
                wstawiono = true;
                array.add(i, input);
                break;
            }
            i++;
        }
        if(wstawiono == false){
            array.add(i, input);
        }
    }
    void rankprint(){
        for(int i = 0; i < array.size(); i++){
            System.out.println(array.get(i));
        }
    }
    rank rankremove(){
        rank zwrot = array.get(array.size() - 1);
        array.remove(array.size() - 1);
        return zwrot;
    }
}