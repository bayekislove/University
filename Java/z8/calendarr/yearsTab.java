package calendarr;

import javax.swing.JPanel;

import java.awt.event.*;
import java.awt.*;

public class yearsTab extends JPanel
{
    Window w;
    monthsPanel[] months;
    int year;
    int monthSelected;
    DateManagement maneg;
    monthsTab a;

    public yearsTab(int year, DateManagement maneg, monthsTab a, Window upper)
    {
        this.w = upper;
        this.a = a;
        monthSelected = 0;
        this.maneg = maneg;
        this.setLayout(new GridLayout(3, 4));
        this.year = year;
        months = new monthsPanel[12];

        for(int i = 0; i < 12; i++)
        {
            months[i] = new monthsPanel(this.year, i);
            this.add(months[i]);
        }

        this.addMouseListener(
            new MouseAdapter(){
                public void mouseClicked(MouseEvent e){
                    int cRow = (e.getY() * 3) / getHeight();
                    int cCol = (e.getX() * 4)/  getWidth();
                    monthSelected = cRow * 4 + cCol;

                    maneg.setMonth(monthSelected);
                    w.scrollBar.setValue(monthSelected);
                    a.update();
                }
            });
    }

    public void updateYear()
    {
        this.year = maneg.getYear();
        for(int i = 0; i < 12; i++)
        {
            months[i].changeYear(this.year);
        }
    }
}
