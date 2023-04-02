package com.in28m.gamerest.game;

import org.springframework.stereotype.Component;

@Component
public class PacmanGame implements GamingConsole {

    public void up(){
        System.out.println("Turn up");
    }
    
    public void down(){
        System.out.println("Turn down");
    }
    
    public void left(){
        System.out.println("Turn left");
    }
    
    public void right(){
        System.out.println("Turn right");
    }

}
