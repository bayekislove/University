package task10game;

import java.util.concurrent.ThreadLocalRandom;

public class Kid implements Runnable
{
    int index;
    int col;
    int row;
    int fieldCrossed;
    boolean sleeping;
    boolean giftReceived;
    gameModel model;

    public Kid(int kCol, int kRow, gameModel board)
    {
        col = kCol; row = kRow; model = board;
        fieldCrossed = 0;
        sleeping = false;
        giftReceived = false;
    }

    @Override
    public void run()
    {
        try
        {
            Thread.sleep( ThreadLocalRandom.current().nextInt(1000, 5000) );
        } 
        catch (InterruptedException e) { }
        
        while( !giftReceived )
        {
            checkSantaCaught();

            int[] path = model.getShortestWayToSanta(this.col, this.row); //[row, col]
            if( path != null && model.checkPosition(path[0], path[1]) == 0 )
            {
                model.makeChildMove(this.row, this.col, path[0], path[1]);
                this.row = path[0];
                this.col = path[1];
            }

            path = model.getShortestWayToSanta(this.col, this.row);
            if( path != null && model.checkPosition(path[0], path[1]) == 0 )
            {
                model.makeChildMove(this.row, this.col, path[0], path[1]);
                this.row = path[0];
                this.col = path[1];
            }

            checkSantaCaught();

            try
            {
                Thread.sleep( ThreadLocalRandom.current().nextInt(1000, 3000) );
            } 
            catch (InterruptedException e) { }
        }   
    }

    public void checkSantaCaught()
    {
        if( model.checkFieldType( this.col, this.row, 2 ) )
            model.receiveGameLostMessage();
    }
}