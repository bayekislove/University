package calendarr;

import java.awt.event.*;
import java.awt.*;

import javax.swing.*;
import javax.swing.event.*;

public class Window extends JFrame 
{
    DateManagement dateManeg;

    monthsTab months;
    yearsTab years;
    JTabbedPane overlaps;
    JToolBar bottomTools;

    JButton prev = new JButton(new AbstractAction("Poprzedni") {

        @Override
        public void actionPerformed(ActionEvent e) {
            dateManeg.decYear();
            years.updateYear();
            months.update();
            spinner.setValue(dateManeg.getYear());
        }
    });

    JButton next = new JButton(new AbstractAction("Następny") {

        @Override
        public void actionPerformed(ActionEvent e) {
            dateManeg.incYear();
            years.updateYear();
            months.update();
            spinner.setValue(dateManeg.getYear());
        }
    });

    JSpinner spinner;
    JScrollBar scrollBar;

    public Window() 
    {
        this.setSize(650, 650);;
        this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        dateManeg = new DateManagement();

        overlaps = new JTabbedPane();

        months = new monthsTab(dateManeg); 
        years = new yearsTab(dateManeg.getYear(), dateManeg, months, this);

        overlaps.addTab("Lata", years);
        overlaps.addTab("Miesiące", months);

        this.setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));
        this.add(overlaps);

        bottomTools = new JToolBar();
        bottomTools.setLayout(new GridLayout(1, 4));
        bottomTools.add(prev); bottomTools.add(next);

        spinner = new JSpinner();
        spinner.addChangeListener(new ChangeListener(){

            @Override
            public void stateChanged(ChangeEvent e) {
                int neww = (int)spinner.getValue();
                dateManeg.setYear(neww);
                years.updateYear();
                months.update();
            }
        });

        spinner.setValue(dateManeg.getYear());
        bottomTools.add(spinner);

        scrollBar = new JScrollBar(Scrollbar.HORIZONTAL, dateManeg.getMonth(), 1, 0, 12);
        scrollBar.addAdjustmentListener(new AdjustmentListener(){
            @Override
            public void adjustmentValueChanged(AdjustmentEvent e) {
                dateManeg.setMonth(scrollBar.getValue());
                months.update();
            }
        });

        bottomTools.add(scrollBar);
        this.add(bottomTools);

        this.setTitle("Kalendarz");
        this.setVisible(true);
    }
}