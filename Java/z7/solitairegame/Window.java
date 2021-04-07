package solitairegame;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class Window 
{
    JFrame mainWindow = new JFrame();

    boardPanel boardd;
    JMenuBar bar;

    JMenu gra = new JMenu("Gra");
    JMenuItem nowa = new JMenuItem(new AbstractAction("Nowa"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.table = new BoardManagement(english.isSelected() ? 1 : 0);
            setMessage(false);
            boardd.fieldClicked = false;
            boardd.indexClicked = -1;
            boardd.repaint();
            mainWindow.setVisible(true);
        }
    });

    JMenuItem koniec = new JMenuItem(new AbstractAction("Koniec"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            System.exit(0);
        }
    });

    JMenu ruchy = new JMenu("Ruchy");
    JMenuItem up = new JMenuItem(new AbstractAction("W górę"){
        @Override
        public void actionPerformed(ActionEvent e) 
        {
            if(boardd.table.makeMove(boardd.indexClicked, 0, true))
                boardd.repaint();
        }
    });
    
    JMenuItem down = new JMenuItem(new AbstractAction("W dół"){
        @Override
        public void actionPerformed(ActionEvent e) 
        {
            if(boardd.table.makeMove(boardd.indexClicked, 2, true))
                boardd.repaint();
        }
    });

    JMenuItem left = new JMenuItem(new AbstractAction("W lewo"){
        @Override
        public void actionPerformed(ActionEvent e) 
        {
            if(boardd.table.makeMove(boardd.indexClicked, 3, true))
                boardd.repaint();
        }
    });

    JMenuItem right = new JMenuItem(new AbstractAction("W prawo"){
        @Override
        public void actionPerformed(ActionEvent e) 
        {
            if(boardd.table.makeMove(boardd.indexClicked, 1, true))
                boardd.repaint();
        }
    });

    JMenu ustawienia = new JMenu("Ustawienia");

    ButtonGroup modeTable = new ButtonGroup();
    JRadioButtonMenuItem english = new JRadioButtonMenuItem(new AbstractAction("Plansza angielska"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.table = new BoardManagement(1);
            setMessage(false);
            boardd.fieldClicked = false;
            boardd.indexClicked = -1;
            boardd.repaint();
        }
    });

    JRadioButtonMenuItem european = new JRadioButtonMenuItem(new AbstractAction("Plansza europejska"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.table = new BoardManagement(0);
            setMessage(false);
            boardd.fieldClicked = false;
            boardd.indexClicked = -1;
            boardd.repaint();
        }
    });

    ButtonGroup modeFront = new ButtonGroup();
    JRadioButtonMenuItem MAGENTA = new JRadioButtonMenuItem(new AbstractAction("Kamyk MAGENTA"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.frontColor = Color.MAGENTA;
            boardd.repaint();
        }
    });

    JRadioButtonMenuItem red = new JRadioButtonMenuItem(new AbstractAction("Kamyk czerwony"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.frontColor = Color.red;
            boardd.repaint();
        }
    });

    ButtonGroup modeBack = new ButtonGroup();
    JRadioButtonMenuItem white = new JRadioButtonMenuItem(new AbstractAction("Tło białe"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.backColor = Color.white;
            boardd.repaint();
        }
    });

    JRadioButtonMenuItem gray = new JRadioButtonMenuItem(new AbstractAction("Tło szare"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.backColor = Color.gray;
            boardd.repaint();
        }
    });

    ButtonGroup selected = new ButtonGroup();
    JRadioButtonMenuItem yellow = new JRadioButtonMenuItem(new AbstractAction("Zaznaczony żółty"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.selectedColor = Color.yellow;
            boardd.repaint();
        }
    });

    JRadioButtonMenuItem blue = new JRadioButtonMenuItem(new AbstractAction("Zaznaczony niebieski"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            boardd.selectedColor = Color.blue;
            boardd.repaint();
        }
    });

    JMenu pomoc = new JMenu("Pomoc");
    JMenuItem autor = new JMenuItem(new AbstractAction("O autorze"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            JOptionPane.showMessageDialog(mainWindow, "Siema");
        }
    });

    JMenuItem help = new JMenuItem(new AbstractAction("O aplikacji"){
        @Override
        public void actionPerformed(ActionEvent e)
        {
            JOptionPane.showMessageDialog(mainWindow, "No ogólnie napisałem se aplikacje");
        }
    });

    JLabel message;
    
    public Window()
    {
        mainWindow = new JFrame();
        mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        bar = new JMenuBar();
        
        gra.add(nowa); gra.addSeparator(); gra.add(koniec);
        bar.add(gra);

        ruchy.add(up); ruchy.add(down); ruchy.add(left); ruchy.add(right);

        up.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_W, 0));
        down.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, 0));
        left.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, 0));
        right.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D, 0));

        bar.add(ruchy);

        modeTable.add(english); ustawienia.add(english);
        modeTable.add(european); ustawienia.add(european);
        ustawienia.addSeparator();
        modeFront.add(red); ustawienia.add(red);
        modeFront.add(MAGENTA); ustawienia.add(MAGENTA);
        ustawienia.addSeparator();
        modeBack.add(white); ustawienia.add(white);
        modeBack.add(gray); ustawienia.add(gray);
        ustawienia.addSeparator();
        selected.add(yellow); ustawienia.add(yellow);
        selected.add(blue); ustawienia.add(blue);
        ustawienia.addSeparator();

        bar.add(ustawienia);

        pomoc.add(autor); pomoc.add(help);
        bar.add(pomoc);

        mainWindow.add(bar, BorderLayout.PAGE_START);

        boardd = new boardPanel(new BoardManagement(1), this);
        boardd.setVisible(true);
        mainWindow.add(boardd);

        message = new JLabel();
        this.setMessage(false);
        mainWindow.add(message, BorderLayout.PAGE_END);

        mainWindow.setSize(700,700);
        mainWindow.setVisible(true);

        mainWindow.setTitle("Kamyszki");

        mainWindow.addComponentListener(new ComponentAdapter(){
            @Override
            public void componentResized(ComponentEvent e) {
                System.out.println(mainWindow.getContentPane().getHeight());
                System.out.println(mainWindow.getContentPane().getWidth());
                int side = Math.min(mainWindow.getContentPane().getHeight(), mainWindow.getContentPane().getWidth());
                boardd.cellSize = (side - 49) / 7;
                boardd.setSize(side - 49, side - 49);
                boardd.repaint();
            }
        });
    }

    public void setMessage(boolean won)
    {
        if(won)
            message.setText("Wygrałeś");
        else
            message.setText("Zbij jeszcze " + (boardd.table.getLeft() - 1) + " Kamyszów, żeby wygrać!");
    }
}
