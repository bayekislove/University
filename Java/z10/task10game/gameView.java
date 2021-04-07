package task10game;

import javax.swing.*;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.Timer;

import java.awt.*;
import java.awt.event.*;
import java.awt.event.KeyEvent;

public class gameView
{
    public JFrame win;
    JPanel panel;
    JLabel[] cells;
    gameController controller;
    int colNum; int rowNum;
    final String[] texts = {"", "K", "S", "P"};

    public gameView(int colNum, int rowNum, gameController controller)
    {
        this.colNum = colNum; 
        this.rowNum = rowNum;
        this.controller = controller;

        this.win = new JFrame();
        win.setTitle("Santa and the kids");
        win.setSize(colNum * 40, rowNum * 40);

        this.panel = new JPanel();
        this.panel.setLayout( new GridLayout(rowNum, colNum) );
        win.add( panel );

        this.cells = new JLabel[colNum * rowNum];

        for(int i = 0; i < colNum * rowNum; i++)
        {
            cells[i] = new JLabel("", SwingConstants.CENTER);
            cells[i].setBorder( BorderFactory.createLineBorder(Color.red) );
            panel.add(cells[i]);
        }

        win.addKeyListener(
            new KeyAdapter(){
                @Override
                public void keyPressed(KeyEvent ev)
                {
                    switch( ev.getKeyCode())
                    {
                        case KeyEvent.VK_LEFT:
                            controller.makeMove(3);
                            break;
                        case KeyEvent.VK_RIGHT:
                            controller.makeMove(1);
                            break;
                        case KeyEvent.VK_UP:
                            controller.makeMove(0);
                            break;
                        case KeyEvent.VK_DOWN:
                            controller.makeMove(2);
                            break;
                    }
                }});

        new Timer(50, new ActionListener()
        {
            public void actionPerformed(ActionEvent ev)
            {
                updateOutlook( controller.getBoard() );
            }
        } ).start();

        win.setVisible(true);
        win.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
    }

    public void showGameLost()
    {
        JOptionPane.showMessageDialog(win, "You lost :(");
        System.exit(0);
    }

    public void showGameWon()
    {
        JOptionPane.showMessageDialog(win, "You won :)");
        System.exit(0);
    }

    public void updateOutlook(int[][] board)
    {
        for(int r = 0; r < rowNum; r++)
        {
            for(int c = 0; c < colNum; c++)
            {
                cells[r * colNum + c].setText( texts[ board[r][c] ] );
            }
        }
    }
}