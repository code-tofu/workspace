package com.in28m.gamerest;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

import com.in28m.gamerest.game.GameRunner;
import com.in28m.gamerest.game.GamingConsole;
import com.in28m.gamerest.game.MarioGame;
import com.in28m.gamerest.game.PacmanGame;
import com.in28m.gamerest.game.SuperContraGame;

@SpringBootApplication
public class GamerestApplication {

	public static void main(String[] args) {

		ConfigurableApplicationContext context = SpringApplication.run(GamerestApplication.class, args);

		/* no longer needed because of spring 
		MarioGame game1 = new MarioGame();
		SuperContraGame game2 = new SuperContraGame();
		PacmanGame game3 = new PacmanGame();
		GamingConsole game4 = new PacmanGame();
		GameRunner runner = new GameRunner(game3); //interfaces allow gamerunner to run any of the types of game
		 */

		GameRunner runner = context.getBean(GameRunner.class); 
		runner.run();
	}

}
