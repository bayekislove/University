package calendarr;

import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.*;

public class monthsPanel extends JPanel
{
    JLabel[] days;
    int year; int month;
    GregorianCalendar pomCalendar;
    Color bgColor;

    public monthsPanel(int year, int month)
    {
        this.setLayout(new GridLayout(6,7));

        pomCalendar = (GregorianCalendar)Calendar.getInstance();
        pomCalendar.set(GregorianCalendar.MONTH, month);
        pomCalendar.set(GregorianCalendar.YEAR, year);
        pomCalendar.set(GregorianCalendar.DAY_OF_MONTH, 1);
        
        this.year = year; this.month = month;
        days = new JLabel[42]; //we can leave it blank if its needed

        for(int i = 0; i < 42; i++)
        {
            this.days[i] = new JLabel();
            this.add(this.days[i]);
        }

        this.updateOutlook();
    }

    public void changeYear(int newYear)
    {
        this.year = newYear;
        this.updateOutlook();
    }

    private void updateOutlook()
    {
        pomCalendar = (GregorianCalendar)Calendar.getInstance();
        pomCalendar.set(GregorianCalendar.MONTH, month);
        pomCalendar.set(GregorianCalendar.YEAR, year);
        pomCalendar.set(GregorianCalendar.DAY_OF_MONTH, 1);

        int startIndex = pomCalendar.get(GregorianCalendar.DAY_OF_WEEK) - 2;
        startIndex = startIndex < 0 ? 6 : startIndex;

        int day = 1; int maxDay = pomCalendar.getActualMaximum(GregorianCalendar.DAY_OF_MONTH);

        setBackground(bgColor);
        for(int i = 0; i < startIndex; i++)
        {
            days[i].setForeground(Color.BLACK);
            days[i].setText("");
        }
            
        for(int i = startIndex; i < 42 && day <= maxDay; i++)
        {
            pomCalendar.set(GregorianCalendar.DAY_OF_MONTH, day);
            days[i].setForeground(pomCalendar.get(GregorianCalendar.DAY_OF_WEEK) == 1 ? Color.RED : Color.BLACK);

            days[i].setText(Integer.toString(day));
            if(year == 1582 && month == 9 && day == 4) 
                day += 10;
            day++;
        }

        if(year == 1582 && month == 9) maxDay -= 10;
            
        for(int i = startIndex + maxDay; i < 42; i++)
        {
            days[i].setForeground(Color.BLACK);
            days[i].setText("");
        }
    }
}
