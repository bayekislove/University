package solitairegame;

import javax.swing.*;

import java.awt.event.*;
import java.awt.Color;
import java.awt.Graphics;

public class boardPanel extends JPanel
{
    Window pom;
    Color backColor;
    Color frontColor;
    Color selectedColor;
    BoardManagement table;
    public int cellSize;
    boolean fieldClicked = false;
    int indexClicked;

    public boardPanel(BoardManagement table, Window pom_window)
    {
        this.pom = pom_window;
        this.table = table; this.cellSize = 94;
        selectedColor = Color.yellow; frontColor = Color.red; backColor = Color.white;

        addMouseListener( new MouseAdapter() {
            public void mouseClicked(MouseEvent e) 
            {
                int row = (e.getY() / cellSize);
                int col = (e.getX() / cellSize);
                int indexx = row * table.size + col;

                if(e.getButton() == MouseEvent.BUTTON1)
                {
                    if(fieldClicked)
                    {
                        if(table.makeMove(indexClicked, (short) (indexx)))
                            pom.setMessage(table.gameEnded());
                        fieldClicked = false;
                        indexClicked = -1;
                    }
                    else //any field not clicked
                    {   
                        fieldClicked = true;
                        indexClicked = indexx;
                    }
                    repaint();
                }
                if(e.getButton() == MouseEvent.BUTTON3)
                {
                    fieldClicked = true;
                    indexClicked = indexx;
                    repaint();

                    JPopupMenu pop = new JPopupMenu();

                    if(table.makeMove(indexx, 0, false)){
                        pop.add(new JMenuItem(new AbstractAction("W górę"){
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                table.makeMove(indexx, 0, true);
                                actoinsAfterMove();
                            }
                        }));}
                    
                    if(table.makeMove(indexx, 1, false)){
                        pop.add(new JMenuItem(new AbstractAction("W prawo"){
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                table.makeMove(indexx, 1, true);
                                actoinsAfterMove();
                            }
                        }));}

                    if(table.makeMove(indexx, 2, false))
                        pop.add(new JMenuItem(new AbstractAction("W dół"){
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                table.makeMove(indexx, 2, true);
                                actoinsAfterMove();
                            }
                        }));

                    if(table.makeMove(indexx, 3, false))
                        pop.add(new JMenuItem(new AbstractAction("W lewo"){
                            @Override
                            public void actionPerformed(ActionEvent e) {
                                table.makeMove(indexx, 3, true);
                                actoinsAfterMove();
                            }
                        }));

                    pop.show(e.getComponent(), e.getX(), e.getY());
                }
            }
        });
    }

    private void actoinsAfterMove()
    {
        pom.setMessage(table.gameEnded());
        fieldClicked = false;
        indexClicked = -1;
        repaint();
    }

    @Override
    public void paintComponent(Graphics g) 
    {
        setBackground(backColor);
        super.paintComponent(g);
        for(int i = 0; i < (table.size * table.size) - 1; i++)
        {
            g.setColor(frontColor);
            if(table.board.tab[i] != -1)
            {
                g.drawRect(i % table.size * cellSize, i / table.size * cellSize, cellSize, cellSize);
                if(table.board.tab[i] == 1)
                {
                    if(i == indexClicked)
                        g.setColor(selectedColor);
                    g.fillOval(i % table.size * cellSize + 3, i / table.size * cellSize + 3, cellSize - 6,  cellSize - 6);
                }
            }
        }
    }
}
