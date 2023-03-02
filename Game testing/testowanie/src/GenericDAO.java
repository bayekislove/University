public class GenericDAO {
    Session s;
    public DbLogger dblog;
    GenericDAO(Session s){
        this.s = s;
    }
    void save() throws SessionOpenException{
        s.open();
        s.startTransaction();
        s.save();
        try {
            s.commitTransaction();
            s.closeSession();
        } catch (CommitException e) {
            dblog.log(e);
            s.closeSession();
        }
    }
}
