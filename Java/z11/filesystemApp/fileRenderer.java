package filesystemApp;

import java.awt.Color;
import java.awt.Component;

import javax.swing.DefaultListCellRenderer;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListCellRenderer;

import java.io.File;

import java.util.Date;

public class fileRenderer implements ListCellRenderer {

    protected DefaultListCellRenderer dRenderer = new DefaultListCellRenderer();

    @Override
    public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
            boolean cellHasFocus) 
    {
        String resString;
        File filePom = (File)value;

        if(index == 0 && (filePom).getParent() == null )
            resString = "../";
        else
            resString = filePom.getName() 
            + "    " + 
            (new Date(filePom.lastModified()).toString());

        JLabel renderer = (JLabel) dRenderer.getListCellRendererComponent(list, resString, index, isSelected, cellHasFocus);

        if(resString.equals("../")) return renderer;

        renderer.setToolTipText( ((double)filePom.length() / 1024) + "kB" );
        if( filePom.isDirectory() )
            renderer.setForeground( Color.ORANGE );

        return renderer;
    }
    
}
