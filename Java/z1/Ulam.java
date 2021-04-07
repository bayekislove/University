public class Ulam {
    private int[][] tab;
    private int tabSize;

    Ulam(int size){
        tabSize = size;
        if((2 > size) || (size > 200)){
            throw new IllegalArgumentException("parametr spoza zakresu 2...200");
        }

        tab = new int[size][size];
        
        int column = size % 2 == 0 ? size/2 - 1 : size/2; 
        int row = size/2; //that's where we start -> in the middle of our array
        int direction = 0; //shows in which direction we need to go
        int howManyMovesNeeded = 1; 
        int movesMade = 0;

        for(int i=1; i <= size * size; i++){
            tab[row][column] = i;
            movesMade++;
            if(movesMade == howManyMovesNeeded){
                movesMade = 0;
                direction++;

                if(direction % 2 == 1 && howManyMovesNeeded != 1) howManyMovesNeeded++;
                if(direction == 3 && howManyMovesNeeded == 1) howManyMovesNeeded++;
                
                if(direction == 4) direction = 0;    
            }

            if(direction == 0) row++;
            if(direction == 1) column++;
            if(direction == 2) row--;
            if(direction == 3) column--;

        }
    }

    void crossNonPrimesOut(){
        for(int i = 0; i < tabSize; i++){
            for(int j = 0; j < tabSize; j++){
                if(!ifPrime(this.tab[i][j])) { this.tab[i][j] = 0; }
            }
        }
    }

    void printUlam(){
        this.crossNonPrimesOut();
        for(int i = 0; i < tabSize; i++){
            for(int j = 0; j < tabSize; j++){
                System.out.print(tab[i][j] == 0 ? " " : "*");
            }
            System.out.println();
        }
    }

    public static boolean ifPrime(int num){
        if(num == 2) return true;
        if(num == 0 || num == 1) return false;
        if(num % 2 == 0) return false;
        for(int i = 3; i <= Math.sqrt(num); i += 2){
            if(num % i == 0) return false;
        }
        return true;
    }   
}