public class aspirant implements rank {
    @Override
    public int get_rank(){
        return 40;
    }
    public int compareTo(rank input){
        if(this.get_rank() < input.get_rank()){
            return -1;
        }
        else if(this.get_rank() > input.get_rank()){
            return 1;
        }
        return 0;
    }
}
