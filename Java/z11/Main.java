import java.io.File;

import filesystemApp.*;

public class Main
{
    public static void main(String[] args) 
    {
        System.out.println((new File("C://")).getParent());
        new appController();
    }
}