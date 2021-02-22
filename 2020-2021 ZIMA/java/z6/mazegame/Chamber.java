package mazegame;

import java.util.ArrayList;

public class Chamber 
{
    public final int size;
    ArrayList<Integer>[] possibleWays;
    private int[] visited;

    public Chamber(int size)
    {
        this.size = size;
        visited = new int[this.size * this.size];
        this.createPossibleWays();
    }

    private void createPossibleWays()
    {    
        possibleWays = new ArrayList[this.size * this.size];

        for (int i = 0; i < size*size; i++) { possibleWays[i] = new ArrayList<Integer>(); };
        int randrow = (int)(Math.random() * (size));
        int randcol = (int)((Math.random() * size));
        ways( randrow, randcol );
    }

    private void ways(int row, int column)
    {
        int index = row * this.size + column;
        visited[index] = 1;

        ArrayList<Integer> directions = new ArrayList<Integer>();

        if(row < size - 1) directions.add(index + size);
        if(row > 0) directions.add(index - size);
        if(column > 0) directions.add(index - 1);
        if(column < size - 1) directions.add(index + 1);

        while(!directions.isEmpty())
        {
            int randomPath = (int)(Math.random() * (directions.size())); //this gives us random way
            int pWay = directions.get(randomPath); //this gives us index we go at

            if( visited[pWay] == 0)
            {
                this.possibleWays[index].add(pWay);
                this.possibleWays[pWay].add(index);
                ways(pWay / size, pWay % size);
            }
            directions.remove(randomPath);
        }
    }

    public boolean movePossible(int start, int end)
    {
        return possibleWays[start].contains(end);
    }

    public ArrayList<Integer> connectionsPossible(int field) { return possibleWays[field]; };
}
