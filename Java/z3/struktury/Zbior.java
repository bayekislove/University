package struktury;

public abstract class Zbior {
    public abstract Para search (String k) throws Exception;
    public abstract void insert (Para p) throws Exception;
    public abstract void delete (String k);
    public abstract double read (String k) throws Exception;
    public abstract void set(Para p) throws Exception;
    public abstract void clean();
    public abstract int how_many();
}
