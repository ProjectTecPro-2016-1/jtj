#ifndef JACK_H
#define JACK_H

#include "gameobject.h"
#include "level.h"
#include <string>

class Jack : public GameObject {
    SDL_Surface *jack;			// Pointer for Jack's graphic elements.

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

        Jack(std::string filename);
        ~Jack();

        bool isDead();

        void die();
        void setSpriteClips();
        void move(int xBegin, int xRange, int yBegin, int yRange);
        void pushMove(int v);
        void popMove(int v);
        void jump(Level* level);

        int getXPosition();
        int getYPosition();

        void pushBox();

        int setLimit(int value, int limit1, int range);
};

#endif
