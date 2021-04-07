package struktury;

public class Para{
    public final String key;
    private double value;

    public Para(String kkey, double vvalue)
    {

        if(!kkey.equals(kkey.toLowerCase()))
            throw new IllegalArgumentException("key musi zawierać tylko małe litery");
        
        else if(kkey == null || kkey.isEmpty())
            throw new IllegalArgumentException("key jest pusty");

        for (char literka : kkey.toCharArray()) {
            if(!(literka >= 'a' && literka <= 'z'))
                throw new IllegalArgumentException("key musi zawierać tylko litery angielskiego alfabetu");
        }

        this.key = kkey; this.value = vvalue; 
    }

    public double getValue()
    {
        return value;
    }

    public void setValue(double inp)
    {
        value = inp;
    }

    @Override
    public boolean equals(Object inpObject){
        if(inpObject instanceof Para) return ((Para)inpObject).key.equals(this.key);
        return false;
    }

    public String toString() {
        return "key: " + key + ";;; value: " + Double.toString(value);
    }
}
