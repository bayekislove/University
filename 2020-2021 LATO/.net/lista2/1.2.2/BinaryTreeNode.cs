using System;
using System.Collections;
using System.Collections.Generic;

namespace _1._2._2
{
    public class BinaryTreeNode<T> 
    {
        public T val { get; set; }
        public BinaryTreeNode<T> left { get; set; }
        public BinaryTreeNode<T> right { get; set; }
        
        public BinaryTreeNode() { }
        public BinaryTreeNode( T val)
        {
            this.val = val;
        }

        public IEnumerable BFSEnumerator()
        {
            return new BinaryTreeBFS(this);
        }

        public IEnumerable DFSEnumerator()
        {
            return new BinaryTreeDFS(this);
        }

        public IEnumerable yieldDFSEnumerator()
        {
            yield return this.val;
            if ( this.left != null)
            {
                foreach ( T val in this.left.yieldDFSEnumerator() )
                {
                    yield return val;
                }
            }
            if (this.right != null)
            {
                foreach (T val in this.right.yieldDFSEnumerator() )
                {
                    yield return val;
                }
            }
        }

        public IEnumerable yieldBFSEnumerator()
        {
            Queue<BinaryTreeNode<T>> en = new Queue<BinaryTreeNode<T>>();
            en.Enqueue( this );
            while( en.Count > 0)
            {
                BinaryTreeNode<T> curr = en.Dequeue();
                yield return curr.val;

                if( curr.left != null )
                    en.Enqueue( curr.left );

                if( curr.right != null )
                    en.Enqueue( curr.right );
            }
        }

        public class BinaryTreeDFS : IEnumerable
        {
            BinaryTreeNode<T> root;
            public BinaryTreeDFS( BinaryTreeNode<T> root )
            {
                this.root = root;
            }
            public IEnumerator GetEnumerator()
            {
                return new BinaryTreeDFSIterator(this.root);
            }
        }

        public class BinaryTreeDFSIterator : IEnumerator<T>
        {
            Stack< BinaryTreeNode<T>> st = new Stack<BinaryTreeNode<T>>();
            BinaryTreeNode<T> start;
            public BinaryTreeDFSIterator( BinaryTreeNode<T> root)
            {
                this.start = new BinaryTreeNode<T>()
                {
                    left = root
                };
                st.Push(start);
            }
            public T Current => st.Peek().val;

            object IEnumerator.Current => st.Peek().val;

            public void Dispose() { }

            public bool MoveNext()
            {
                BinaryTreeNode<T> curr = st.Pop();
                if (curr.right != null)
                    st.Push(curr.right);
                if (curr.left != null)
                    st.Push(curr.left);
                return st.Count != 0;
            }

            public void Reset()
            {
                st.Clear();
                st.Push(start);
            }
        }

        public class BinaryTreeBFS : IEnumerable
        {
            BinaryTreeNode<T> root;
            public BinaryTreeBFS(BinaryTreeNode<T> root)
            {
                this.root = root;
            }

            public IEnumerator GetEnumerator()
            {
                return new BinaryTreeBFSIterator(this.root);
            }
        }

        public class BinaryTreeBFSIterator : IEnumerator<T>
        {
            Queue<BinaryTreeNode<T>> en = new Queue<BinaryTreeNode<T>>();
            BinaryTreeNode<T> start;

            public BinaryTreeBFSIterator(BinaryTreeNode<T> root)
            {
                this.start = new BinaryTreeNode<T>() 
                {
                    left = root 
                };
                en.Enqueue(start);
            }
            public T Current => en.Peek().val;

            object IEnumerator.Current => en.Peek().val;

            public void Dispose() { }

            public bool MoveNext()
            {
                BinaryTreeNode<T> curr = en.Dequeue();
                if (curr.left != null)
                    en.Enqueue(curr.left);

                if (curr.right != null)
                    en.Enqueue(curr.right);
                return en.Count != 0;
            }

            public void Reset()
            {
                en = new Queue<BinaryTreeNode<T>>();
                en.Enqueue(this.start);
            }
        }
    }
}
