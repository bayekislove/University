package task10game;

public class gameController 
{
    int rows, cols;
    gameModel model;
    gameView view;

    public gameController(int cols, int rows)
    {
        model = new gameModel(cols, rows, this);
        view = new gameView(cols, rows, this);
    }

    public void handleGameLost()
    {
        view.showGameLost();
    }

    public void handleGameWon()
    {
        view.showGameWon();
    }

    public void makeMove(int direction)
    {
        model.makeSantaMove(direction);
    }

    public int[][] getBoard()
    {
        return model.getBoard();
    }
}
