package calendarr;

import java.util.GregorianCalendar;

public class DateManagement 
{
    GregorianCalendar calendar; //this calendar represents current selected data in programme
    
    public DateManagement()
    {
        calendar = (GregorianCalendar)GregorianCalendar.getInstance();
    }

    public void decYear() { calendar.add(GregorianCalendar.YEAR, -1); }

    public void incYear() { calendar.add(GregorianCalendar.YEAR, 1); }

    public int getYear() { return calendar.get(GregorianCalendar.YEAR); };

    public int getMonth() { return calendar.get(GregorianCalendar.MONTH); };

    public void setMonth(int inp) { calendar.set(GregorianCalendar.MONTH, inp); } 

    public void setYear(int inp) { calendar.set(GregorianCalendar.YEAR, inp); } 

    public int getYearPrev() 
    { 
        return calendar.get(GregorianCalendar.YEAR) + (calendar.get(GregorianCalendar.MONTH) == 0 ? -1 : 0);
    }

    public int getYearNext()
    {
        return calendar.get(GregorianCalendar.YEAR) + (calendar.get(GregorianCalendar.MONTH) == 11 ? 1 : 0);
    }

    public int getMonthPrev()
    {
        return calendar.get(GregorianCalendar.MONTH) == 0 ? 11 : calendar.get(GregorianCalendar.MONTH) - 1;
    }

    public int getMonthNext()
    {
        return calendar.get(GregorianCalendar.MONTH) == 11 ? 0 : calendar.get(GregorianCalendar.MONTH) + 1;
    }
}