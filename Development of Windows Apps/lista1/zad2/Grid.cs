namespace zad2
{
    class Grid
    {
        /// <summary>
        /// Field holding element's values in Grid
        /// </summary>
        private int[,] tab;
        /// <summary>
        /// size of columns in Grid
        /// </summary>
        private int colSize;
        /// <summary>
        /// size of row in Grid
        /// </summary>
        private int rowSize;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="row">Number of rows</param>
        /// <param name="col">Number of columns</param>
        public Grid(int row, int col)
        {
            tab = new int[row, col];
            this.colSize = col;
            this.rowSize = row;
        }

        /// <summary>
        /// One dimension indexer
        /// </summary>
        /// <param name="rowIdx"></param>
        /// <returns></returns>
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
        /// <summary>
        /// Two dimensional indexer
        /// </summary>
        /// <param name="r">indexed row</param>
        /// <param name="c">indexed col</param>
        /// <returns>Element in array if getter is called, nothing otherwise</returns>
        public int this[int r, int c]
        {
            get => tab[r, c];
            set => tab[r, c] = value;
        }
    }
}
