package freezemonsters;

import spriteframework.sprite.BadSprite;
import spriteframework.Commons;

import javax.swing.ImageIcon;
import java.awt.Image;

public class SlimeProjectile extends BadSprite {

    private int dx;
    private int dy;
    private boolean destroyed;

    public SlimeProjectile(int x, int y, int dx, int dy) {
        this.x = x;
        this.y = y;
        this.dx = dx;
        this.dy = dy;

        this.destroyed = false;
        loadImage();
    }

    private void loadImage() {
        String projectileImg = "images/gosma.png";
        ImageIcon ii = new ImageIcon(projectileImg);
        Image projectileImage = ii.getImage();
        projectileImage = projectileImage.getScaledInstance(25,25, Image.SCALE_DEFAULT);
        setImage(projectileImage);
    }

    @Override
    public void act() {
        if (!destroyed) {
            x += dx;
            y += dy;

            // Verifica se saiu da tela
            if (x < 0 || x > Commons.BOARD_WIDTH || y < 0 || y > Commons.BOARD_HEIGHT) {
                destroyed = true;
                setVisible(false);
            }
        }
    }

    public void setDestroyed(boolean destroyed) {
        this.destroyed = destroyed;
        if (destroyed) {
            setVisible(false);
        }
    }

    public boolean isDestroyed() {
        return destroyed;
    }
}
