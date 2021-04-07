package mazegame;

import java.awt.*;
import java.awt.event.*;;

public class Window 
{
    Frame win = new Frame("main");
    Labirynth map = new Labirynth(10);

    public Window(int nFields)
    {
        win.setResizable(false);
        win.setTitle("Play Maaazzzeee!");
        win.setFocusable(true);
        win.setVisible(true);
        win.setSize(614, 637);

        GameCanvas view = new GameCanvas(this);

        win.add(view);

        win.addWindowListener(
            new WindowAdapter(){
                public void windowClosing(WindowEvent ev) { win.dispose(); };
            }
        );

        win.addKeyListener(
            new KeyAdapter(){
                @Override
                public void keyPressed(KeyEvent ev)
                {
                    boolean moveMade = false;
                    switch( ev.getKeyCode())
                    {
                        case KeyEvent.VK_LEFT:
                            moveMade = map.movePossible(0);
                            break;
                        case KeyEvent.VK_RIGHT:
                            moveMade = map.movePossible(1);
                            break;
                        case KeyEvent.VK_UP:
                            moveMade = map.movePossible(2);
                            break;
                        case KeyEvent.VK_DOWN:
                            moveMade = map.movePossible(3);
                            break;
                        case 'r':
                            map = new Labirynth(10);
                            break;
                    }

                    if(moveMade)
                        view.repaint();
                    if(map.getPlayerPosition() == 0)

                        map = new Labirynth(10);
                }});
    }
}
