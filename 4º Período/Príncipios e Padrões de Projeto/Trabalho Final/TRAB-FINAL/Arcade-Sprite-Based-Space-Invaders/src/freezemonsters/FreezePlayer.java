package freezemonsters;

import spriteframework.sprite.Player;
import spriteframework.Commons;

import javax.swing.ImageIcon;
import java.awt.*;
import java.awt.event.KeyEvent;

public class FreezePlayer extends Player {

    public enum Direction {
        UP, DOWN, LEFT, RIGHT
    }

    private int dy; // deslocamento vertical
    private Direction direction;

    public FreezePlayer() {
        super();
        direction = Direction.UP; // Direção padrão
    }

    @Override
    protected void loadImage() {
        String woodyImg = "/images/woody.png"; // Caminho correto no classpath
        ImageIcon ii = new ImageIcon(getClass().getResource("/images/woody.png"));
        Image image = ii.getImage().getScaledInstance(40, 60, Image.SCALE_SMOOTH);

        ImageIcon scaledIcon = new ImageIcon(image);
        setImage(scaledIcon.getImage());
    }

    @Override
    public void act() {
        x += dx;
        y += dy;

        // Impedir que saia da tela
        if (x < 0) x = 0;

        if (x > Commons.BOARD_WIDTH - getImageWidth() - 15){
            x = Commons.BOARD_WIDTH - getImageWidth() - 15;
        }

        if (y < 0) y = 0;
        if (y > Commons.BOARD_HEIGHT - getImageHeight() - 40){
            y = Commons.BOARD_HEIGHT - getImageHeight() - 40;
        }
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();

        switch (key) {
            case KeyEvent.VK_LEFT:
                dx = -2;
                direction = Direction.LEFT;
                break;
            case KeyEvent.VK_RIGHT:
                dx = 2;
                direction = Direction.RIGHT;
                break;
            case KeyEvent.VK_UP:
                dy = -2;
                direction = Direction.UP;
                break;
            case KeyEvent.VK_DOWN:
                dy = 2;
                direction = Direction.DOWN;
                break;
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();

        switch (key) {
            case KeyEvent.VK_LEFT:
            case KeyEvent.VK_RIGHT:
                dx = 0;
                break;
            case KeyEvent.VK_UP:
            case KeyEvent.VK_DOWN:
                dy = 0;
                break;
        }
    }

    public Direction getDirection() {
        return direction;
    }


}
