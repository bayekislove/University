package task10game;

import java.util.concurrent.ThreadLocalRandom;

public class gameModel 
{
    gameController controller;
    int cols, rows;
    Thread[] kidsThreads;
    Kid[] kids;
    int[][] fields;
    int santaRow, santaCol;
    int kidsReceived;

    public gameModel(int cols, int rows, gameController cont)
    {
        this.cols = cols; 
        this.rows = rows;
        this.controller = cont;

        fields = new int[cols][rows];
        kidsThreads = new Thread[12];
        kids = new Kid[12];
        kidsReceived = 0;

        boardSantaKidsInit();
    };

    public void boardSantaKidsInit()
    {
        santaCol = ThreadLocalRandom.current().nextInt(cols);
        santaRow = ThreadLocalRandom.current().nextInt(rows);
        fields[santaRow][santaCol] = 2;
        int kidRow, kidCol;

        for(int i = 0; i < 12; )
        {
            kidCol = ThreadLocalRandom.current().nextInt(cols);
            kidRow = ThreadLocalRandom.current().nextInt(rows);

            if( !checkFieldType(kidCol, kidRow, 2) && !checkFieldType(kidCol, kidRow, 1) )
            {
                kids[i] =  new Kid(kidCol, kidRow, this);
                kidsThreads[i] = new Thread( kids[i] );
                fields[kidRow][kidCol] = 1;
                i++;
            }
        }

        for(int i = 0; i < 2; i++){ kidsThreads[i].start(); };
    }

    public synchronized int checkPosition(int col, int row)
    { 
        synchronized(fields)
        {
            return fields[row][col]; 
        }
    };

    public void receiveGameLostMessage()
    {
        controller.handleGameLost();
    }

    public void receiveGameWonMessage()
    {
        controller.handleGameWon();
    }

    //2 stands for Santa, 3 for gift
    public synchronized boolean checkFieldType(int cCol, int cRow, int fieldType)
    {   
        synchronized(fields)
        {
            int upRow = cRow == 0 ? rows - 1 : cRow - 1;
            int downRow = cRow == rows - 1 ? 0 : cRow + 1;
            int leftCol = cCol == 0 ? cols - 1 : cCol - 1;
            int rightCol = cCol == cols - 1 ? 0 : cCol + 1;

            return (checkPosition(leftCol, cRow) == fieldType || checkPosition(cCol, downRow) == fieldType ||
                    checkPosition(rightCol, cRow) == fieldType || checkPosition(cCol, upRow) == fieldType);
        }
    }

    public synchronized int[] getShortestWayToSanta(int cCol, int cRow)
    {
        synchronized(fields)
        {
            if(Math.abs(cCol - santaCol) > 5 && Math.abs(cRow - santaRow) > 5)
                return null;
            int[] retTab = new int[2];
            if( Math.abs( cCol - santaCol ) >= Math.abs( cRow - santaRow ) )
            {
                retTab[1] = cCol + ( (int)Math.signum( santaCol - cCol ) ) ;
                retTab[0] = cRow;
            } 
            else 
            {
                retTab[0] = cRow + ( (int)Math.signum( santaRow - cRow ) );
                retTab[1] = cCol;
            }
            return retTab;
        }
    }

    public synchronized void makeChildMove(int sRow, int sCol, int eRow, int eCol)
    {
        synchronized(fields)
        {
            fields[sRow][sCol] = 0;
            fields[eRow][eCol] = 1;
        }   
    }

    public synchronized void makeSantaMove(int direction)
    {
        synchronized(this)
        {
            int oldRow = santaRow; int oldCol = santaCol;
        
            if(direction == 0 || direction == 2)
            {
                if(direction == 0)
                    santaRow = santaRow == 0 ? rows - 1 : santaRow - 1;
                else 
                    santaRow = santaRow == rows - 1 ? 0 : santaRow + 1;;
            } 
            else 
            {
                if(direction == 1)
                    santaCol = santaCol == cols - 1 ? 0 : santaCol + 1;
                else
                    santaCol = santaCol == 0 ? cols - 1 : santaCol - 1;
            }

            if( checkPosition(santaCol, santaRow) == 0 )
            {
                fields[oldRow][oldCol] = 0;
                fields[santaRow][santaCol] = 2;
            } 
            else
            {
                santaRow = oldRow;
                santaCol = oldCol;
            }
            
            for (Kid kid : kids) 
            {
                if( checkFieldType(kid.col, kid.row, 2) )
                {
                    kid.giftReceived = true;
                    kidsReceived++;
                }
            }
            
            if(kidsReceived == 4) controller.handleGameWon();
        }
    }

    public int[][] getBoard(){ return this.fields; };
}
