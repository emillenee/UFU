package freezemonsters;

import spriteframework.sprite.BadSprite;
import spriteframework.Commons;

import javax.swing.ImageIcon;
import java.awt.Image;

public class FreezeRay extends BadSprite {
    private int dx;
    private int dy;

    public FreezeRay(int x, int y, FreezePlayer.Direction direction) {
        this.x = x;
        this.y = y;

        loadImage();

        switch (direction) {
            case UP:
                dx = 0;
                dy = -5;
                break;
            case DOWN:
                dx = 0;
                dy = 5;
                break;
            case LEFT:
                dx = -5;
                dy = 0;
                break;
            case RIGHT:
                dx = 5;
                dy = 0;
                break;
        }
    }

    private void loadImage() {
        String rayImg = "images/ray.png";
        ImageIcon ii = new ImageIcon(rayImg);
        Image rayImage = ii.getImage();
        rayImage = rayImage.getScaledInstance(25,25, Image.SCALE_DEFAULT);
        setImage(rayImage);
    }

    public void deactivate() {
        setVisible(false);
    }

    @Override
    public void act() {
        x += dx;
        y += dy;

        // Verifica se o FreezeRay ultrapassou os limites da tela (se sim, desativar)
        if (x < 0 || x > Commons.BOARD_WIDTH || y < 0 || y > Commons.BOARD_HEIGHT) {
            setVisible(false);
        }
    }
}
