#ifndef JACK_H
#define JACK_H

#include "gameobject.h"
#include "level.h"
#include <string>

class Jack : public GameObject {
    SDL_Surface *jack;			// Pointer for Jack's graphic elements.

    // -------------------------------------------------------------
	// Function: drawSelf()
	// Description: Selects the current motion frame and draws Jack's image in specific position
	//				on the screen according to it's attributes.
	// Parameters:
	//		SDL_Surface * surface;	Pointer for surface in which graphic components will be drawn
	// Attributes: nothing
	// Return: void
	// -------------------------------------------------------------
    void drawSelf(SDL_Surface *surface);
    int x_position;				// Variable that store Jack's position in X axis.
	int y_position;				// Variable that store Jack's position in Y axis.
	bool dead;					// Stores the information whether Jack is dead or not.
	int lastMove;				// Stores Jack's last move. Used to stop Jack or make him walk again.
	int lastButOneMove;			// Stores Jack's last but one move. Used to stop Jack or make him walk again.
	int frame; 					// Variable for animation in drawSelf() method.

    SDL_Rect spriteClips[9];
    public:
        int	strength;				// Stores Jack's strength to move boxes.
    	int speed;					// Stores Jack's actual horizontal speed.
    	int verticalSpeed;			// Stores Jack's actual vertical Speed.
    	bool jumping;				// Stores the information wheter Jack is jumping or not.
        static const int ACCELERATION = 1;		// Used to increment the speed in the Y axis;
    	static const int JACK_WIDTH = 38;		// Jack's horizontal size.
    	static const int JACK_HEIGHT = 57;		// Jack's vertical size.

        // -------------------------------------------------------------
    	// Function: Jack()
    	// Description: Jack class builder where the initializations of the variables happen.
    	// Parameters:
    	//		string filename;	Name of the file from which will be loaded Jack's image.
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        Jack(std::string filename);

        // -------------------------------------------------------------
    	// Function: ~Jack()
    	// Description: Jack class destructor in which images files free themselves.
    	// Parameters: void
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        ~Jack();

        // -------------------------------------------------------------
    	// Function: isDead()
    	// Description:	Return the boolean variable indicating whether Jack is dead or not.
    	// Parameters: void
    	// Attributes: nothing
    	// Return: bool
    	// -------------------------------------------------------------
        bool isDead();

        // -------------------------------------------------------------
    	// Function: die()
    	// Description:	Gives the true value to the boolean variable "dead".
    	// Parameters: void
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void die();

        // -------------------------------------------------------------
    	// Function: setSpriteClips()
    	// Description: Initializes the dimensions of each picture frame and each Jack's moviment.
    	// Parameters: void
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void setSpriteClips();

        // -------------------------------------------------------------
    	// Function: move()
    	// Description: Method that calls setLimit() to assure Jack's won't pass screen's limits.
    	// Parameters:
    	//		int xBegin;		Limit in some of Jack's directions in X axis.
    	//		int xRange;		Range in X axis.
    	//		int yBegin;		Limit in some of Jack's directions in Y axis.
    	//		int yRange;		Range in Y axis.
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void move(int xBegin, int xRange, int yBegin, int yRange);

        // -------------------------------------------------------------
    	// Function: pushMove()
    	// Description: Method that makes Jack move again after pausing.
    	// Parameters:
    	//		int v;		Variable that will make Jack walk again.
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void pushMove(int v);

        // -------------------------------------------------------------
    	// Function: popMove()
    	// Description:	Method that stops Jack when pausing.
    	// Parameters:
    	//		int v;		Variable that will stop Jack's movement.
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void popMove(int v);

        // -------------------------------------------------------------
    	// Function: jump()
    	// Description:	Controls the act of jumping and its consequences with respect to the maximum
    	//				height and possible collisions with some box.
    	// Parameters:
    	//		Level * level;		Pointer to access level class.
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void jump(Level* level);

        // -------------------------------------------------------------
    	// Function: getXPosition()
    	// Description:	Returns the current Jack's position on the X axis.
    	// Parameters: void
    	// Attributes: nothing
    	// Return: int
    	// -------------------------------------------------------------
        int getXPosition();

        // -------------------------------------------------------------
    	// Function: getYPosition()
    	// Description:	Returns the current Jack's position on the Y axis.
    	// Parameters: void
    	// Attributes: nothing
    	// Return: int
    	// -------------------------------------------------------------
        int getYPosition();

        // -------------------------------------------------------------
    	// Function: pushBox()
    	// Description: Does nothing.
    	// Parameters: void
    	// Attributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void pushBox();

        // -------------------------------------------------------------
    	// Function: setLimit()
    	// Description:	Method that assures Jack won't pass specified limits.
    	// Parameters:
    	//		int value;		Value referent to Jack's actual position.
    	//		int limit1;		Limit to some of Jack's directions.
    	//		int range;		Range of the direction specified in limit1.
    	// Attributes:
    	//		int limit2;		Limit to opposite Jack's direction in limit1;
    	// Return: void
    	// -------------------------------------------------------------
        int setLimit(int value, int limit1, int range);
};

#endif
