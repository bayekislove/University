import java.util.HashMap;

public class Car {
    public int id;
    public HashMap<String, Long> yearMileage;

    public Car CarDAO(int id)
    {
        return new Car();
    }

    public long findMileageBetweenYears(int id, String start, String end)
    {
        Car car = this.CarDAO(id);
        long sum = 0l;

        for(String year : car.yearMileage.keySet())
        {
            if(Long.parseLong(year) <= Long.parseLong(end) && 
               Long.parseLong(year) >= Long.parseLong(start))
            {
                sum += car.yearMileage.get(year);
            }
        }
        return sum;
    }
}
