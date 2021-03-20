using System;

namespace _1._2._2
{
    class Program
    {
        static void Main(string[] args)
        {
            BinaryTreeNode<int> root = new BinaryTreeNode<int>(1)
            {
                left = new BinaryTreeNode<int>(2)
                {
                    left = new BinaryTreeNode<int>(4)
                },
                right = new BinaryTreeNode<int>(3)
            };

            foreach( int s in root.yieldBFSEnumerator() )
            {
                Console.WriteLine(s);
            }

            Console.WriteLine();

            foreach ( int s in root.BFSEnumerator() )
            {
                Console.WriteLine(s);
            }

            Console.WriteLine();

            foreach (int s in root.yieldDFSEnumerator())
            {
                Console.WriteLine(s);
            }

            Console.WriteLine();

            foreach (int s in root.DFSEnumerator())
            {
                Console.WriteLine(s);
            }
        }
    }
}
