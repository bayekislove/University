package mazegame;

import java.awt.*;
import java.awt.image.*;
import java.io.*;
import java.util.ArrayList;
import javax.imageio.*;

public class GameCanvas extends Canvas 
{
    private static final long serialVersionUID = 1L;
    int width;
    Window win;
    int pX; int pY;
    Graphics2D table;

    public GameCanvas(Window win) {
        this.win = win;
        width = 600;
        setSize(600, 600);
        setBackground(Color.white);
        setVisible(true);
    }

    public void paint(Graphics gr) 
    {
        this.table = (Graphics2D) gr;
        table.setColor(Color.black);
        table.setStroke(new BasicStroke(10));

        for (int i = 0; i < 11; i++) {
            table.drawLine(i * 60, 0, i * 60, width);
            table.drawLine(0, i * 60, width, i * 60);
        }

        for (int i = 0; i < win.map.chamSize * win.map.chamSize - 1; i++) {
            int iRow = i / win.map.chamSize;
            int iCol = i % win.map.chamSize;
            ArrayList<Integer> pom = win.map.chamber.connectionsPossible(i);
            for (Integer h : pom) {
                table.setColor(Color.white);

                if (h == i + 1) {
                    table.drawLine((iCol + 1) * 60, iRow * 60 + 10, (iCol + 1) * 60, (iRow + 1) * 60 - 10);
                } else if (h == i - 1)
                    table.drawLine(iCol * 60, iRow * 60 + 10, iCol * 60, (iRow + 1) * 60 - 10);
                else if (h > i) {
                    table.drawLine(iCol * 60 + 10, (iRow + 1) * 60, (iCol + 1) * 60 - 10, (iRow + 1) * 60);
                } else if (h < i)
                    table.drawLine(iCol * 60 + 10, iRow * 60, (iCol + 1) * 60 - 10, iRow * 60);
            }
        }

        pY = win.map.playerRow;
        pX = win.map.playerCol;

        try 
        {
            BufferedImage img = ImageIO.read(new File("mazegame/explorer.jpg"));
            table.drawImage(img, pX * 60 + 15, pY * 60 + 15, 40, 40, null);
        } 
        catch (IOException e) { }
    }

    public void update(Graphics g) {
        Graphics offgc;
        Image offscreen = null;
        Dimension d = getSize();

        offscreen = createImage(d.width, d.height);
        offgc = offscreen.getGraphics();
        offgc.setColor(Color.white);
        offgc.fillRect(0, 0, d.width, d.height);
        offgc.setColor(Color.black);

        paint(offgc);
        g.drawImage(offscreen, 0, 0, this);
    }
}
