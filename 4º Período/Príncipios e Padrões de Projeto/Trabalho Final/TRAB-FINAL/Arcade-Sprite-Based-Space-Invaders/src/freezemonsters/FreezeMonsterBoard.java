package freezemonsters;

import spriteframework.Commons;

import spriteframework.AbstractBoard;
import spriteframework.sprite.Player;
import spriteframework.sprite.BadSprite;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.util.LinkedList;
import java.util.Random;

public class FreezeMonsterBoard extends AbstractBoard {

    // Lista de projéteis congelantes e gosmas
    private LinkedList<FreezeRay> freezeRays;
    private LinkedList<SlimeProjectile> slimes;

    @Override
    protected Player createPlayer() {
        return new FreezePlayer();
    }

    @Override
    protected void createBadSprites() {
        for (int i = 0; i < 9; i++) {
            MonsterSprite monster = MonsterFactory.createRandomMonster(i);
            badSprites.add(monster);
        }
    }



    @Override
    protected void createOtherSprites() {
        freezeRays = new LinkedList<>();
        slimes = new LinkedList<>();
    }

    @Override
    protected void drawOtherSprites(Graphics g) {
        // desenha os raios congelantes
        for (FreezeRay ray : freezeRays) {
            if (ray.isVisible()) {
                g.drawImage(ray.getImage(), ray.getX(), ray.getY(), this);
            }
        }

        // desenha as gosmas dos monstros
        for (SlimeProjectile slime : slimes) {
            if (slime.isVisible()) {
                g.drawImage(slime.getImage(), slime.getX(), slime.getY(), this);
            }
        }
    }

    @Override
    protected void processOtherSprites(Player player, KeyEvent e) {
        int key = e.getKeyCode();

        if (key == KeyEvent.VK_SPACE) {
            // Verifica se já existe um FreezeRay visível
            boolean hasRay = false;
            for (FreezeRay r : freezeRays) {
                if (r.isVisible()) {
                    hasRay = true;
                    break;
                }
            }

            // Só cria um novo raio se não houver nenhum ativo
            if (!hasRay) {
                FreezePlayer woody = (FreezePlayer) player;
                FreezeRay ray = new FreezeRay(woody.getX(), woody.getY(), woody.getDirection());
                freezeRays.add(ray);
            }
        }
    }


    @Override
    protected void update() {
        for (Player player : players) {
            player.act();
        }

        for (FreezeRay ray : freezeRays) {
            ray.act();

            if (!ray.isVisible()) continue;

            for (BadSprite sprite : badSprites) {
                if (!sprite.isVisible()) continue;

                if (sprite instanceof MonsterSprite mon && !mon.isFrozen() &&
                        ray.getRect().intersects(mon.getRect())) {
                    mon.freeze();
                    ray.deactivate();
                    break;
                }
            }

            // Verifica colisão do raio com gosmas
            for (SlimeProjectile slime : slimes) {
                if (!slime.isDestroyed() && ray.getRect().intersects(slime.getRect())) {
                    slime.setDestroyed(true);
                    ray.deactivate();
                    break;
                }
            }
        }

        // Atualiza os monstros
        for (BadSprite monster : badSprites) {
            monster.act();
        }

        // Atualiza gosmas
        for (SlimeProjectile slime : slimes) {
            slime.act();
        }

        // Verifica derrota
        Player player = getPlayer(0);
        if (player != null && player.isVisible()) {
            for (SlimeProjectile slime : slimes) {
                if (!slime.isDestroyed() && slime.getRect().intersects(player.getRect())) {
                    slime.setDestroyed(true);
                    player.setDying(true);
                }
            }
        }

        // Verifica vitória (todos congelados)
        boolean allFrozen = true;
        for (BadSprite b : badSprites) {
            if (b instanceof MonsterSprite m && !m.isFrozen()) {
                allFrozen = false;
                break;
            }
        }

        if (allFrozen) {
            inGame = false;
            message = "Você venceu!";
            timer.stop();
        }

        // Gosmas lançadas pelos monstros (aleatoriamente)
        Random random = new Random();
        for (BadSprite b : badSprites) {
            if (b.isVisible()) {
                SlimeProjectile slime = b.tryToShootSlime(random);
                if (slime != null) {
                    slimes.add(slime);
                }
            }
        }

    }

    @Override
    protected Color getBackgroundColor() {
        return new Color(34, 139, 34);
    }
}
