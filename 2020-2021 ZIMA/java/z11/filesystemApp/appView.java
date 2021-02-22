package filesystemApp;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.io.File;

import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JToolBar;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class appView {
    JFrame win;
    JLabel folderName;
    JScrollPane pane;
    JList list;
    JFileChooser fileChooser;
    JToolBar buttonsToolBar;
    JButton folderChooserButton;
    JButton copyButton;
    JButton deleteButton;
    JButton changeEncodingButton;
    JButton changeNameButton;

    appController controller;

    public appView( appController controller, filesList inpFilesList )
    {
        this.controller = controller;

        win = new JFrame();
        win.setTitle( "Filesystem app" );
        win.setSize( 650, 650 );
        win.setResizable( false );
        win.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

        File startFile = new File("C://");

        folderName = new JLabel( startFile.getAbsolutePath() );
        folderName.setForeground( Color.red );
        win.getContentPane().add( folderName, BorderLayout.PAGE_START );

        pane = new JScrollPane(list);
    
        list = new JList(inpFilesList);
        list.setCellRenderer(new fileRenderer());

        win.getContentPane().add(list, BorderLayout.CENTER);

        fileChooser = new JFileChooser(startFile);
        fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

        buttonsToolBar = new JToolBar();
        folderChooserButton = new JButton(new AbstractAction("Open") 
        {
            @Override
            public void actionPerformed(ActionEvent e) 
            {
                int returnVal = fileChooser.showOpenDialog(win);
                System.out.println(returnVal);
                if(returnVal == JFileChooser.APPROVE_OPTION) 
                {
                    controller.handleDirectoryChanged( fileChooser.getSelectedFile() );
                }
            }
        });
        buttonsToolBar.add(folderChooserButton);

        copyButton = new JButton( new AbstractAction("Copy") 
        {
            @Override
            public void actionPerformed(ActionEvent e) 
            {
                controller.handleCopyFile();
            }
        } );
        buttonsToolBar.add(copyButton);

        deleteButton = new JButton( new AbstractAction("Delete") 
        {
            @Override
            public void actionPerformed(ActionEvent e) 
            {
                if( JOptionPane.showConfirmDialog(win ,"Are you sure?", "", JOptionPane.YES_NO_OPTION ) == JOptionPane.YES_OPTION )
                    controller.handleDeleteFile();
            }
        } );
        buttonsToolBar.add(deleteButton);

        changeEncodingButton = new JButton( new AbstractAction("Change encoding") 
        {
            @Override
            public void actionPerformed(ActionEvent e) 
            {
                controller.handleDeleteFile();
            }
        } );
        buttonsToolBar.add(changeEncodingButton);

        changeNameButton = new JButton( new AbstractAction("Change name") 
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                controller.handleRename( JOptionPane.showInputDialog(win, "New name") );
            }
        });
        buttonsToolBar.add(changeNameButton);

        list.addMouseListener(new MouseAdapter()
        {
            @Override
            public void mouseClicked(MouseEvent ev)
            {
                int index = ev.getY() / folderName.getHeight();
                if( index > list.getModel().getSize() ) return;
                
                if(ev.getClickCount() == 1)
                    controller.handleFileMarked(index);

                else if(ev.getClickCount() == 2)
                    controller.handleDirectoryChanged( (File)list.getModel().getElementAt( index ) );
            }
        });
        
        win.getContentPane().add(buttonsToolBar, BorderLayout.PAGE_END);
        win.setVisible(true);
    }

    public void changeCurrDirectory(String newDir)
    {
        folderName.setText( newDir );
    }
}