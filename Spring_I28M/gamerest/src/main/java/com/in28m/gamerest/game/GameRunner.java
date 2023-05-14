package com.in28m.gamerest.game;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class GameRunner {

    // private SuperContraGame game;
    // private MarioGame game;
    @Autowired //autowire to reduce dependency
    private GamingConsole game;

    public GameRunner(GamingConsole game) {
        this.game = game;
    }

	public void run() {
		game.up();
		game.down();
		game.left();
		game.right();
	}

}
