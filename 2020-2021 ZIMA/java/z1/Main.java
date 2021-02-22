public class Main{
    public static void main(String[] args){
        for(int i = 0; i < args.length; i++){
            int pom = Integer.parseInt(args[i]);
            (new Ulam(pom)).printUlam();
            if(i != args.length - 1){
                System.out.println("");
                System.out.println("");
                System.out.println("");
            }
        }
    } 
}