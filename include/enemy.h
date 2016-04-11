#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "box.h"
#include <string>
#include <vector>

class Enemy : public GameObject {
    SDL_Surface *enemy;    // Pointer for enemy graphic elements.

    // -------------------------------------------------------------
	// Function: drawSelf()
	// Description: Selects the current motion frame and draws the enemies image in specific position
	//				on the screen according to the enemy attributes.
	// Parameters:
	//		SDL_Surface *surface;  		Pointer for surface where the graphic component will be drawn .
	// Atributes: nothing
	// Return: void
	// -------------------------------------------------------------
    void drawSelf(SDL_Surface *surface);

    int frame;   // Keeps the actual frame value.
    SDL_Rect spriteClips[8];    // Contains the dimensions of each motion frame.
    public:
        // -------------------------------------------------------------
    	// Function: setSpriteClips()
    	// Description: Initializes the dimensions of each picture frame and each enemy moviment.
    	// Parameters: void
    	// Atributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void setSpriteClips();
        int x_position;	  // Axis X position where the enemy is localizated.
    	int y_position;	  // Axis Y position where the enemy is localizated.
    	int movesLeft;	  // Controls the enemy movements to the right.
    	int moveDirection;  // Controls the movements direction horizontally.
        static const int ENEMY_WIDTH = 38;    // Contains the enemies width from each position occupied on screen.
    	static const int ENEMY_HEIGHT = 57;	  // Contains the enemies height from each position occupied on screen.

        // -------------------------------------------------------------
    	// Function: Enemy()
    	// Description: Enemy class builder where the initializations of the variables happen.
    	// Parameters:
    	//		string fileName;  		Enemy landscape file name.
    	// Atributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        Enemy(std::string filename);

        // -------------------------------------------------------------
    	// Function: ~Enemy()
    	// Description: Enemy class destructor where the landscape image files free themselves.
    	// Parameters: void
    	// Atributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        ~Enemy();

        // -------------------------------------------------------------
    	// Function: move()
    	// Description: Moves the enemy horizontally according to level dimensions.
    	// Parameters: void
    	// Atributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void move();

        // -------------------------------------------------------------
    	// Function: throwBox()
    	// Description: Controls the enemies freedom box when the right position is achieved.
    	// Parameters:
    	//		int vector<Box*> boxes;			Vector that contains boxes it´s positions.
    	// Atributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void throwBox(vector<Box*> boxes);
};

#endif
