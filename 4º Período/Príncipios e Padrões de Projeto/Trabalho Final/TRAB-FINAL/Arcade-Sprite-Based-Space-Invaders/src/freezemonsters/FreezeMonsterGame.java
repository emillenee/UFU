package freezemonsters;

import java.awt.EventQueue;
import spriteframework.AbstractBoard;
import spriteframework.MainFrame;

public class FreezeMonsterGame extends MainFrame {

    public FreezeMonsterGame() {
        super("Freeze Monster");
    }

    @Override
    protected AbstractBoard createBoard() {
        return new FreezeMonsterBoard();
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> new FreezeMonsterGame());
    }
}

