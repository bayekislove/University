package struktury;

public class ZbiorNaTablicy extends Zbior
 {
    Para[] dict;
    int size;
    int how_many_elements;

    public ZbiorNaTablicy(int ssize)
    {
        if(ssize < 2 || ssize > Integer.MAX_VALUE)
            throw new IllegalArgumentException("Podaj rozmiar mieszczący się w zakresie inta i mniejszy od 2");

        dict = new Para[ssize];
        how_many_elements = 0; 
        size = ssize;
    }

    @Override
    public Para search(String k) throws Exception
    {
        for (Para para : dict) 
        {
            if(para != null && (para.key).equals(k))
                return para;
        }

        throw new Exception("Podanego klucza nie ma w słowniku");
    }

    @Override
    public void insert(Para p) throws Exception
    {
        if(how_many_elements == size)
            throw new Exception("Słownik pełny!");
        
        int index_to_insert = size - 1;

        for (int i = 0; i < size; i++) 
        {
            if(this.dict[i] == null){
                index_to_insert = i;
                break;
            }
                
            else if(dict[i].equals(p))
                throw new Exception("Para o tym kluczu jest już w słowniku!");
        }
        
        dict[index_to_insert] = p;
        how_many_elements++;
    }

    @Override
    public void delete(String k)
    {
        for(int i = 0; i < size; i++)
        {
            if(dict[i] != null && (dict[i].key).equals(k))
            {
                dict[i] = null;
                how_many_elements--;
            }
        }   
    }

    @Override
    public double read(String k) throws Exception
    {
        for(Para para : dict)
        {
            if(para != null && para.key.equals(k))
                    return para.getValue();
        }

        throw new Exception("Nie ma pary o podanym indeksie");
    }

    @Override
    public void set(Para p) throws Exception
    {

        int index_to_insert = size - 1;

        for(int i = 0; i < size; i++)
        {
            if(dict[i] == null)
                index_to_insert = i;

            if(dict[i].equals(p))
            {
                dict[i] = p;
                return; //if we found a pair with the same index as inserted, the job is done
            }
        }
        
        if(how_many_elements == size)
            throw new Exception("Tablica jest pełna i nie ma w niej elementu o podanym indeksie");
        else
            dict[index_to_insert].setValue(p.getValue());
    }

    @Override
    public void clean()
    {
        dict = new Para[size];
        how_many_elements = 0;
    }

    @Override
    public int how_many()
    {
        return how_many_elements;
    }
}