package solitairegame;

public abstract class Board 
{
    protected int[] tab = new int[49];
    protected int occupiedNum = 0;
    protected int size;

    public boolean gameEnded() { return occupiedNum == 1; };

    public boolean move(int start, int end, boolean doIT) //tries to move and returns true if suceeded
    {
        if(tab[end] == -1 || tab[start] == 0 || tab[end] == 1) return false;

        int startRow = start / size;
        int endRow = end / size;

        return checkInDirection(start, end, startRow == endRow ? 1 : size, doIT);
    }

    private boolean checkInDirection(int start, int end, int difference, boolean doIT) //determined by row/column jump
    {
        if(start < end)
        {
            if(tab[start + difference] == 1)
            {
                if(doIT) tab[start + difference] = 0;
            }
            else
                return false;
        }
        else
        {
            if(tab[start - difference] == 1)
            {
                if(doIT) tab[start - difference] = 0;
            }
            else
                return false;
        }
        if(doIT)
        {
            tab[start] = 0;
            tab[end] = 1;
            this.occupiedNum--;
        }
        return true;
    }
}