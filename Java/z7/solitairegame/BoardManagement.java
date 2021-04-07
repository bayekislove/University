package solitairegame;

public class BoardManagement 
{
    Board board;
    int size = 7;

    public BoardManagement(int boardNum) //0 stands for european, 1 for british
    {
        board = boardNum == 0 ? new europeanBoard() : new englishBoard();
    }

    public boolean makeMove(int start, int direction, boolean doIT) //0 - up, 1 - right, 2 - down, 3 - left
    {                                                           //field doIT tells us whether to move if possible
        int startRow = start / size; int startCol = start % size;

        if(direction == 0)
            return startRow < 2 ? false : board.move(start, start - 2 * size, doIT);

        if(direction == 1)
            return startCol > 6 ? false : board.move(start, start + 2, doIT);

        if(direction == 2)
            return startRow > 6 ? false : board.move(start, start + 2 * size, doIT);

        else //direction is 3 then
            return startCol < 2 ? false : board.move(start, start - 2, doIT);
    }

    public boolean makeMove(int start, short end) 
    {
        if(Math.abs(start - end) != 2 && Math.abs(start - end) != 14)
            return false;
        return board.move(start, end, true); 
    };

    public boolean gameEnded() { return board.gameEnded(); };

    public int getLeft() { return board.occupiedNum ;};
}
