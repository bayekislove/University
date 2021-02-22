package calendarr;

import javax.swing.JPanel;
import javax.swing.ListCellRenderer;
import javax.swing.JList;

import java.awt.GridLayout;

public class monthsTab extends JPanel
{
    DateManagement pomManag; 
    ListCellRenderer render;

    JList prevList; JList currList; JList nextList;
    monthListModel prev; monthListModel curr; monthListModel next; 

    public monthsTab(DateManagement pomManag)
    {
        render = new monthsTabCellRenderer();
        this.pomManag = pomManag;

        this.setLayout(new GridLayout(1, 3));

        prev = new monthListModel(pomManag.getYearPrev(), pomManag.getMonthPrev());
        curr = new monthListModel(pomManag.getYear(), pomManag.getMonth());
        next = new monthListModel(pomManag.getYearNext(), pomManag.getMonthNext());

        prevList = new JList(prev);
        currList = new JList(curr);
        nextList = new JList(next);

        prevList.setCellRenderer(render); 
        currList.setCellRenderer(render);
        nextList.setCellRenderer(render);
        
        this.add(prevList); this.add(currList); this.add(nextList);
        
        prev.update(pomManag.getYearPrev(), pomManag.getMonthPrev());
        curr.update(pomManag.getYear(), pomManag.getMonth());
        next.update(pomManag.getYearNext(), pomManag.getMonthNext());
    }

    public void update()
    {
        prev.update(pomManag.getYearPrev(), pomManag.getMonthPrev());
        curr.update(pomManag.getYear(), pomManag.getMonth());
        next.update(pomManag.getYearNext(), pomManag.getMonthNext());
    }
}
