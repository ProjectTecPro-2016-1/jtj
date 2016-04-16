#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "box.h"
#include <string>
#include <vector>

class Enemy : public GameObject {
    SDL_Surface * enemy;     // Pointer for enemy graphic elements.
    void drawSelf(SDL_Surface * surface);

    int frame;                      // Keeps the actual frame value.
    SDL_Rect spriteClips[8];        // Contains the dimensions of each motion frame.
    public:
        void setSpriteClips();
        int x_position;	                        // Axis X position where the enemy is localizated.
    	int y_position;	                        // Axis Y position where the enemy is localizated.
    	int movesLeft;	                        // Controls the enemy movements to the right.
    	int moveDirection;                      // Controls the movements direction horizontally.
        static const int ENEMY_WIDTH = 38;      // Contains the enemies width from each position occupied on screen.
    	static const int ENEMY_HEIGHT = 57;	    // Contains the enemies height from each position occupied on screen.

        Enemy(std::string filename);
        ~Enemy();
        void move();
        void throwBox(vector<Box*> boxes);
};

#endif
