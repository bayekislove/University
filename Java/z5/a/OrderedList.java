package a;

import java.util.Iterator;

public class OrderedList<T extends Comparable<T>> implements OrderedSequence<T>, Iterable<T>
{
    
    private class Node <A extends Comparable<A>>
    {
        private Node<A> next;
        private A data;

        Node(Node<A> nextt, A dataa)
        {   
            next = nextt; data = dataa;
        }

        ///Returns last Node smaller than val
        public Node<A> stopWhenBigEqFound(A val)
        {
            Node<A> current = this;

            while(current.next != null && current.next.data.compareTo(val) < 0)
            {
                current = current.next;
            }

            return current;
        }

        public Node<A> skip(int i)
        {
            Node<A> current = this;

            for(int j = 0; j < i; j++)
            {
                current = current.next;
            }

            return current;
        }
    }

    private int size = 0;
    private Node<T> start = null;

    @Override
    public void insert(T el)
    {
        if(el == null)
            throw new NullPointerException();

        if(start == null || start.data.compareTo(el) > 0)
        {
            Node<T> pom = new Node<T>(start, el);
            this.start = pom;
            this.size++;
            return;
        }

        Node<T> current = start.stopWhenBigEqFound(el);

        if(current.data.compareTo(el) == 0)
            return;
        
        current.next = new Node<T>(current.next, el);
        this.size++;
    }

    @Override
    public void remove(T el)
    {
        if(el == null)
            throw new NullPointerException();

        if(start == null)
            return;

        if(this.start.data.compareTo(el) == 0)
            this.start = start.next;

        Node<T> current = start.stopWhenBigEqFound(el);

        if(current.next.data.compareTo(el) == 0)
        {
            current.next = current.next.next;
            this.size--;
        }
    }

    @Override
    public T min()
    {
        return start.data;
    }

    @Override
    public T max()
    {
        return this.start.skip(size - 1).data;
    }

    @Override
    public T at(int index)
    {
        if(index < 0 || index >= this.size)
            throw new IndexOutOfBoundsException();

        return this.start.skip(index).data;
    }

    @Override
    public int index(T el) throws Exception
    {
        if(el == null)
            throw new NullPointerException();

        Node<T> current = this.start;
        
        int it = 0;
        while(current != null && current.data.compareTo(el) < 0)
        {
            current = current.next;
            it++;
        }

        if(current.data.compareTo(el) == 0)
            return it;
        throw new Exception("There is no such element");
    }

    @Override
    public boolean search(T el)
    {
        return this.start.stopWhenBigEqFound(el).next.data.compareTo(el) == 0;
    }

    @Override
    public Iterator<T> iterator()
    {
        return new OrderedListIterator(this);
    }

    private class OrderedListIterator implements Iterator<T>
    {
        Node<T> current;
        Node<T> lastNext; 

        OrderedListIterator(OrderedList<T> inp)
        {
            current = inp.start;
            lastNext = null;
        }

        @Override
        public boolean hasNext()
        {
            return current != null;
        }

		@Override
        public T next() 
        {
            lastNext = current;
            current = current.next;
            return lastNext.data;
        }
        
        @Override
        public void remove()
        {
            OrderedList.this.remove(lastNext.data);
        }
    }

    @Override
    public String toString()
    {
        String output = "";
        for(T el : this)
        {
            output += el.toString() + " ";
        }
        return output;
    }
}
