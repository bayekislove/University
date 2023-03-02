import static org.mockito.Mockito.*;
import static org.mockito.Mockito.when;

import java.util.HashMap;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(org.mockito.junit.MockitoJUnitRunner.class)
public class CarTests {
    @Test
    public void testSingleYear()
    {
        Car c = spy(new Car());

        Car car = new Car();
        car.id = 70;
        car.yearMileage = new HashMap<String, Long>();
        car.yearMileage.put("1999", 3l);
        car.yearMileage.put("2000", 1l);
        car.yearMileage.put("2001", 300l);

        when(c.CarDAO(70)).thenReturn(car);
        Assert.assertEquals(3l, c.findMileageBetweenYears(70, "1999", "1999"));
    }

    @Test
    public void testNoYears()
    {
        Car c = spy(new Car());

        Car car = new Car();
        car.id = 70;
        car.yearMileage = new HashMap<String, Long>();
        car.yearMileage.put("1999", 3l);
        car.yearMileage.put("2000", 1l);
        car.yearMileage.put("2001", 300l);

        when(c.CarDAO(70)).thenReturn(car);
        Assert.assertEquals(0l, c.findMileageBetweenYears(70, "3000", "3000"));
    }

    @Test
    public void testAllYears()
    {
        Car c = spy(new Car());

        Car car = new Car();
        car.id = 70;
        car.yearMileage = new HashMap<String, Long>();
        car.yearMileage.put("1999", 3l);
        car.yearMileage.put("2000", 1l);
        car.yearMileage.put("2001", 300l);

        when(c.CarDAO(70)).thenReturn(car);
        Assert.assertEquals(304l, c.findMileageBetweenYears(70, "1999", "2001"));
    }
}
