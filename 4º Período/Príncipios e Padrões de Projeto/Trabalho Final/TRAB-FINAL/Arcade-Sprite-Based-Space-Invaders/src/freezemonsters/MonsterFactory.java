package freezemonsters;

import java.util.Random;
import spriteframework.Commons;

public class MonsterFactory {

    private static final Random rand = new Random();

    public static MonsterSprite createRandomMonster(int i) {

        int x = 50 + rand.nextInt(Commons.BOARD_WIDTH - 100);
        int y = 50 + rand.nextInt(Commons.GROUND - 150);

        return new MonsterSprite(x, y, i+1);
    }

    public static MonsterSprite createMonsterAt(int x, int y, int skin) {
        return new MonsterSprite(x, y,skin);
    }
}