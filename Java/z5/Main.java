import a.*;
import java.util.Calendar;

public class Main {
    public static void main(String[] args) throws Exception
    {
        OrderedList<Integer> test = new OrderedList<Integer>();
        test.insert(3);
        test.insert(2);
        test.insert(5);
        System.out.println(test.at(2));

        test.remove(3);
        System.out.println(test.at(1));

        System.out.println("5 jest " + test.search(5));
        test.insert(7);
        test.insert(4);
        test.insert(9);

        System.out.println(test.min());
        System.out.println(test.at(test.index(test.max())));
        test.remove(test.min());
        System.out.println(test.at(0));
        System.out.println();

        for(Integer pom : test)
        {
            System.out.println(pom);
        }
        System.out.println();
        OrderedList<String> test2 = new OrderedList<String>();
        test2.insert("c"); test2.insert("a"); test2.insert("t");

        for(String pom : test2)
        {
            System.out.print(pom);
        }
        
        System.out.println();
        Calendar calendar = Calendar.getInstance();
        Calendar calendar2 = Calendar.getInstance();
        calendar2.add(Calendar.MONTH, -1);
        OrderedList<Calendar> test3 = new OrderedList<Calendar>();
        test3.insert(calendar); test3.insert(calendar2);
        System.out.println();

        for(Calendar pom : test3)
        {
            System.out.println(pom.getTime());
        }
    }
}
