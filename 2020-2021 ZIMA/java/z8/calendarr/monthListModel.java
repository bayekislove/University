package calendarr;

import java.util.GregorianCalendar;

import javax.swing.AbstractListModel;

public class monthListModel extends AbstractListModel
{
    GregorianCalendar pom;
    private static String[] daysNames = {"Niedziela", "Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota"};
    private static String[] monthsNames = {"styczeń", "luty", "marzec", "kwiecień", "maj", "czerwiec", "lipiec", "sierpień", "wrzesień", "październik", "listopad", "grudzień"};

    public monthListModel(int year, int month)
    {
        pom = new GregorianCalendar(year, month, 1);
    }

    public void update(int newYear, int newMonth)
    {
        pom = new GregorianCalendar(newYear, newMonth, 1); //spytać czemu się wywala jak zrobimy pom.set(Month) i pom.set(Yr);
        fireContentsChanged(this, 0, this.getSize());
    }

    @Override
    public int getSize() 
    {
        if(pom.get(GregorianCalendar.YEAR) == 1582 && pom.get(GregorianCalendar.MONTH) == 9)
            return 21;
        return pom.getActualMaximum(GregorianCalendar.DAY_OF_MONTH);
    }

    @Override
    public String getElementAt(int index) 
    {
        if  (pom.get(GregorianCalendar.YEAR) == 1582 && pom.get(GregorianCalendar.MONTH) == 9 && index > 3)
            {
                index += 10;
            }

        pom.set(GregorianCalendar.DAY_OF_MONTH, index + 1);
        String output = "";

        output += Integer.toString(index + 1) + " ";
        output += monthListModel.monthsNames[pom.get(GregorianCalendar.MONTH)] + ", ";
        output += monthListModel.daysNames[pom.get(GregorianCalendar.DAY_OF_WEEK) - 1];

        return output; //"nr_dnia miesiac, dzien_tygodnia"
    }
}