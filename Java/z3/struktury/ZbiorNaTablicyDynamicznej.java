package struktury;

public class ZbiorNaTablicyDynamicznej extends ZbiorNaTablicy{

    public ZbiorNaTablicyDynamicznej()
    {
        super(2);
    }

    @Override
    public void insert(Para p) throws Exception
    {   
        int index_to_insert = size;

        for (int i = 0; i < size; i++) 
        {
            if(this.dict[i] == null)
                index_to_insert = i;
                
            else if(dict[i].equals(p))
                throw new Exception("Para o tym kluczu jest już w słowniku!");
        }
        
        if(index_to_insert == this.size){
            this.rewrite(this.size * 2);
            index_to_insert = how_many_elements;
            size *= 2;
        }

        dict[index_to_insert] = p;
        how_many_elements++;
    }

    @Override
    public void delete(String k)
    {
        for(int i = 0; i < size; i++)
        {
            if(dict[i].key == k)
            {
                dict[i] = null;
                how_many_elements--;
            }
        }

        if(how_many_elements < size / 4)
            this.rewrite(size / 2);
    }

    @Override
    public void set(Para p) throws Exception
    {
        int index_to_insert = 0;

        for(int i = 0; i < size; i++)
        {
            if(dict[i] == null)
                index_to_insert = i;

            if(dict[i].equals(p))
            {
                dict[i].setValue(p.getValue());
                return; //if we found a pair with the same index as inserted, the job is done
            }
        }
        
        if(how_many_elements == size){
            this.rewrite(size * 2);
            size *= 2;
            index_to_insert = how_many_elements;
            how_many_elements++;
        }

        dict[index_to_insert] = p;
    }

    private void rewrite(int new_size)
    {
        Para[] pom = new Para[new_size];
        int new_tab_index = 0;

        for(int i = 0; i < size; i++)
        {
            if(dict[i] != null)
            {
                pom[new_tab_index] = dict[i];
                new_tab_index++;
            }
        }
        this.dict = pom;
    }
}
