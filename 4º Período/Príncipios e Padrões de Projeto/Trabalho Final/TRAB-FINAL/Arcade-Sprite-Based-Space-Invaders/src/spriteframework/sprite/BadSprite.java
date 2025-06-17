package spriteframework.sprite;

import freezemonsters.SlimeProjectile;

import java.util.LinkedList;
import java.util.Random;

public abstract class BadSprite extends Sprite {
	public LinkedList<BadSprite>  getBadnesses() {
		return null;
	}
	public boolean isDestroyed() {
		return false;
	}
	public void act () {
		//
	}
	//método para atirar
	public SlimeProjectile tryToShootSlime(Random random) {
		return null;
	}
}
