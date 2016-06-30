#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.hpp"
#include "box.hpp"
#include <string>
#include <vector>

class Enemy : public GameObject {
    private:
        int xPosition;                          // Axis X position where the enemy is localizated.
        int yPosition;                          // Axis Y position where the enemy is localizated.
        int movesLeft;                          // Controls the enemy movements to the right.
        int moveDirection;                      // Controls the movements direction horizontally.
        int frame;                              // Keeps the actual frame value.

    public:
        void setXPosition(int xPosition);
        int getXPosition();

        void setYPosition(int yPosition);      
        int getYPosition();
        
        void setMovesLeft(int movesLeft);
        int getMovesLeft();
        
        void setMoveDirection(int moveDirection);
        int getMoveDirection();

        void setFrame(int frame);
        int getFrame();

        void FirstMove();
        void SecondMove();
        void ThirdMove();
        void FourthMove();
        void FifthMove();
        
        SDL_Surface * enemy;     // Pointer for enemy graphic elements.
        void drawSelf(SDL_Surface * surface);

        SDL_Rect spriteClips[8];        // Contains the dimensions of each motion frame.
        
        void setSpriteClips();
        static const int ENEMY_WIDTH = 38;      // Contains the enemies width from each position
                                                // occupied on screen.
    	static const int ENEMY_HEIGHT = 57;	    // Contains the enemies height from each position
                                                // occupied on screen.

        Enemy(std::string filename);
        ~Enemy();
        void move();
        
        void throwBox(vector<Box*> boxes);
        void setStopEnemy();
        void setStartingtRightEnemyMovement();
        void setContinuingRightEnemyMovement();
        void setFinishingRightEnemyMovement();
        void setFinishingLeftEnemyMovement();
        void setContinuingLeftEnemyMovement();
        void setStartingtLeftEnemyMovement();
        void setDropBox();
/*
*/
};

#endif
