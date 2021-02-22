package mazegame;

//gives general logic for managing any move betweeen fields/chambers
public class Labirynth 
{
    Chamber chamber;

    int playerRow;
    int playerCol;
    int chamSize;

    public Labirynth(int chamSize)
    {
        this.chamSize = chamSize; 
        chamber = new Chamber(chamSize);

        playerRow = 1 + (int)(Math.random() * (chamSize - 1));
        playerCol = 1 + (int)(Math.random() * (chamSize - 1));
    }
    //0 - left, 1 - right, 2 - up, 3 - down
    public boolean movePossible(int direction)
    {
        int playerIndex = playerRow * chamSize + playerCol;

        int newIndex;

        if(direction == 0)
            newIndex = playerIndex - 1;
        else if(direction == 1)
            newIndex = playerIndex + 1;
        else if(direction == 2)
            newIndex = playerIndex - chamSize;
        else
            newIndex = playerIndex + chamSize; //direction = 3

        if(chamber.movePossible(playerIndex, newIndex))
        {
            playerRow = newIndex / chamSize; playerCol = newIndex % chamSize;
            return true;
        }
        return false;
    }

    public int getPlayerPosition() { return playerRow*chamSize + playerCol; };

}
