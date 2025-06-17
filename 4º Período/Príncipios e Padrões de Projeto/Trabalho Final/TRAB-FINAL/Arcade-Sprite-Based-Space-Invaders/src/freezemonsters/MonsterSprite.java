package freezemonsters;

import spaceinvaders.Commons;
import spriteframework.sprite.BadSprite;
import spriteframework.sprite.BadnessBoxSprite;

import javax.swing.ImageIcon;
import java.awt.*;
import java.util.LinkedList;
import java.util.Random;

public class MonsterSprite extends BadnessBoxSprite{

    private boolean frozen = false;
    private int dx, dy;
    private final Random random = new Random();
    private Image frozenImage;

    // Futuro: gosma que o monstro pode lançar
    private SlimeProjectile slime;

    public MonsterSprite(int x, int y, int skinIndex) {
        this.x = x;
        this.y = y;
        loadImage(skinIndex);
        chooseRandomDirection();
    }

/*
    private void loadImage() {
        String monsterImg = "images/monster1.png";
        ImageIcon ii = new ImageIcon(monsterImg);
        Image monsterImage = ii.getImage();
        monsterImage =monsterImage.getScaledInstance(40,40, Image.SCALE_DEFAULT);
        setImage(monsterImage);
    }
*/
    private void loadImage(int skinIndex) {
    String imgPath = "/images/monster" + skinIndex + ".png";
    String frozenImgPath = "/images/monster" + skinIndex + "bg.png";

    ImageIcon ii = new ImageIcon(this.getClass().getResource(imgPath));
    Image monsterImage = ii.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);
    setImage(monsterImage);

    // Armazena a imagem congelada para usar depois
    this.frozenImage = new ImageIcon(this.getClass().getResource(frozenImgPath)).getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);
    }

    public void freeze() {
        this.frozen = true;
        setImage(frozenImage);
    }

    public boolean isFrozen() {
        return frozen;
    }

    private void chooseRandomDirection() {
        dx = random.nextInt(3) - 1; // -1, 0 ou 1
        dy = random.nextInt(3) - 1;
    }

    @Override
    public void act() {
        if (!frozen) {
            x += dx;
            y += dy;

            // Trocar direção aleatoriamente às vezes
            if (random.nextInt(20) == 0) {
                chooseRandomDirection();
            }

            // Limites da tela
            if (x < 0) x = 0;

            if (x > Commons.BOARD_WIDTH - getImageWidth() - 43){
                x = Commons.BOARD_WIDTH - getImageWidth() - 43;
            }
            if (y < 0) y = 0;

            if (y > Commons.BOARD_HEIGHT - getImageHeight() - 70){
                y = Commons.BOARD_HEIGHT - getImageHeight() - 70;
            }
        }
    }

    @Override
    public LinkedList<BadSprite> getBadnesses() {
        LinkedList<BadSprite> gosmas = new LinkedList<>();
        if (slime != null && !slime.isDestroyed()) {
            gosmas.add(slime);
        }
        return gosmas;
    }

    // Para uso futuro: definir uma nova slime
    public void setSlime(SlimeProjectile slime) {
        this.slime = slime;
    }

    @Override
    public SlimeProjectile tryToShootSlime(Random random) {
        if (isFrozen() || getBadnesses().size() > 0) return null;

        if (random.nextInt(100) < 3) {
            int dx = random.nextInt(3) - 1;
            int dy = random.nextInt(3) - 1;
            if (dx == 0 && dy == 0) dx = 1;

            SlimeProjectile slime = new SlimeProjectile(getX(), getY(), dx, dy);
            setSlime(slime);
            return slime;
        }

        return null;
    }


    public int getDX() {
        return dx;
    }

    public int getDY() {
        return dy;
    }

}
