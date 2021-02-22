package solitairegame;

public class englishBoard extends Board
{
    englishBoard()
    {
        tab = new int[49];
        tab[0] = -1; tab[1] = -1; tab[5] = -1; tab[6] = -1; tab[7] = -1; tab[8] = -1; tab[12] = -1; tab[13] = -1;
        tab[35] = -1; tab[36] = -1; tab[40] = -1; tab[41] = -1; tab[42] = -1; tab[43] = -1; tab[47] = -1; tab[48] = -1;

        for(int i = 0; i < 49; i++) 
            if(tab[i] != -1) tab[i] = 1;

        tab[3 + 3*7] = 0;
        size = 7;
        occupiedNum = 33;
    }
}
