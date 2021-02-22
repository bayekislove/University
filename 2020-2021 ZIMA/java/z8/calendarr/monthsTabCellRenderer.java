package calendarr;

import java.awt.Component;

import java.awt.Color;

import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListCellRenderer;
import javax.swing.DefaultListCellRenderer;

public class monthsTabCellRenderer implements ListCellRenderer {
    protected DefaultListCellRenderer dRenderer = new DefaultListCellRenderer();

    @Override
    public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
        
        JLabel renderer = (JLabel) dRenderer.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);

        if (renderer.getText().contains("Nie")) 
        {
            renderer.setForeground(Color.red);
        }

        return renderer;
    }
}