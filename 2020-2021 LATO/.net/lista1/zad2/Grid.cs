namespace zad2
{
    class Grid
    {
        int[,] tab;
        int colSize, rowSize;
        public Grid(int row, int col)
        {
            tab = new int[row, col];
            this.colSize = col;
            this.rowSize = row;
        }

        public int[] this[int rowIdx]
        {
            get
            {
                int[] returned = new int[colSize];
                for( int i = 0; i < colSize; i++)
                {
                    returned[i] = tab[rowIdx, i];
                }
                return returned;
            }
        }

        public int this[int r, int c]
        {
            get => tab[r, c];
            set => tab[r, c] = value;
        }
    }
}
