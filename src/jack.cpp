#include "jack.h"
#include "level.h"
#include "sdlutil.h"

using namespace std;

// -------------------------------------------------------------
// Function: Jack()
// Description: Jack class builder where the initializations of the variables happen.
// Parameters:
//		string filename;	Name of the file from which will be loaded Jack's image.
// Return: void
// -------------------------------------------------------------
Jack::Jack(string filename) {
    this->jack = SDLUtil::loadImage(filename);
    this->x_position = JACK_WIDTH + Level::LEVEL_X_OFFSET;
    this->y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - Jack::JACK_HEIGHT - 38;
    this->speed = 0;
    this->dead = false;
    verticalSpeed = 0;
    jumping = false;
	lastMove = 0;
	lastButOneMove = 0;
	strength = 0;
    frame = 0;
}

// -------------------------------------------------------------
// Function: ~Jack()
// Description: Jack class destructor in which images files free themselves.
// Return: void
// -------------------------------------------------------------
Jack::~Jack() {
    if(jack != NULL) {
        SDL_FreeSurface(jack);
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------
// Function: die()
// Description:	Gives the true value to the boolean variable "dead".
// Return: void
// -------------------------------------------------------------
void Jack::die() {
    this->dead = true;
}

// -------------------------------------------------------------
// Function: isDead()
// Description:	Return the boolean variable indicating whether Jack is dead or not.
// Return: bool
// -------------------------------------------------------------
bool Jack::isDead() {
    return this->dead;
}

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
int Jack::setLimit(int value, int limit1, int range) {
    int limit2 = limit1 + range;
    int valueForReturn = 0;

    if (value<limit1) {
        valueForReturn = limit1;
    } else if (value >= limit2) {
        valueForReturn = limit2;
    } else {
        valueForReturn = value;
    }

    return valueForReturn;
}

// -------------------------------------------------------------
// Function: drawSelf()
// Description: Selects the current motion frame and draws Jack's image in specific position
//				on the screen according to it's attributes.
// Parameters:
//		SDL_Surface * surface;	Pointer for surface in which graphic components will be drawn
// Return: void
// -------------------------------------------------------------
void Jack::drawSelf(SDL_Surface *surface) {
    if(jumping == true) {
        if(speed >= 0) {
            frame = 7;
        } else {
            frame = 8;
        }
    } else if (speed > 0) {
        frame ++;

        if (frame > 3) {
            frame = 1;
        } else {
            // Nothing to do
        }
    } else if (speed < 0) {
        frame++;

        if (frame < 4) {
            frame = 4;
        } else {
            // Nothing to do
        }

        if (frame > 6) {
            frame = 4;
        } else {
            // Nothing to do
        }
    } else {
        frame = 0;
    }

    SDLUtil::applySurface(this->x_position, this->y_position, this->jack, surface, &spriteClips[frame]);
    return;
}

// -------------------------------------------------------------
// Function: move()
// Description: Method that calls setLimit() to assure Jack's won't pass screen's limits.
// Parameters:
//		int xBegin;		Limit in some of Jack's directions in X axis.
//		int xRange;		Range in X axis.
//		int yBegin;		Limit in some of Jack's directions in Y axis.
//		int yRange;		Range in Y axis.
// Return: void
// -------------------------------------------------------------
void Jack::move(int xBegin, int xRange, int yBegin, int yRange) {
    x_position += speed;

    this->x_position = setLimit(x_position, xBegin, xRange-JACK_WIDTH);
    this->y_position = setLimit(y_position, yBegin, yRange-JACK_HEIGHT - 38);

    return;
}

// -------------------------------------------------------------
// Function: jump()
// Description:	Controls the act of jumping and its consequences with respect to the maximum
//				height and possible collisions with some box.
// Parameters:
//		Level * level;		Pointer to access level class.
// Return: void
// -------------------------------------------------------------
void Jack::jump(Level* level) {
    y_position += verticalSpeed;
    verticalSpeed += ACCELERATION;

    int maxJumpHeightLeft = ((int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 -38 -
                            (level->grid[(x_position - Level::LEVEL_X_OFFSET)/38].size()*38)));
    int maxJumpHeightRight = ((int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 -38 -
                             (level->grid[(x_position+37 - Level::LEVEL_X_OFFSET)/38].size()*38)));

    if(jumping == true) {
        if ((y_position >= maxJumpHeightLeft) || (y_position >= maxJumpHeightLeft)) {
            jumping = false;
            verticalSpeed = 1;
        } else {
            // Nothing to do
        }
    } else {
        // Nothing to do
    }

    //these next two if's handles boxes superior colision.
    if (y_position >= maxJumpHeightLeft) {
        y_position = maxJumpHeightLeft;
        verticalSpeed = 1;
        //verticalSpeed -= ACCELERATION;
    } else if (y_position >= maxJumpHeightRight) {
        y_position = maxJumpHeightRight;
        verticalSpeed = 1;
        //verticalSpeed -= ACCELERATION;
    } else { //this avoids double jumping while falling from a box
        jumping = true;
    }
    //verticalSpeed++;

    return;
}

// -------------------------------------------------------------
// Function: pushMove()
// Description: Method that makes Jack move again after pausing.
// Parameters:
//		int v;		Variable that will make Jack walk again.
// Return: void
// -------------------------------------------------------------
void Jack::pushMove(int v) {
	if (lastMove == 0) {
		speed = v;
		lastMove = v;
	} else if (lastButOneMove == 0) {
		speed = v;
		lastButOneMove = v;
	} else {
        // Nothing to do
    }

    return;
}

// -------------------------------------------------------------
// Function: popMove()
// Description:	Method that stops Jack when pausing.
// Parameters:
//		int v;		Variable that will stop Jack's movement.
// Return: void
// -------------------------------------------------------------
void Jack::popMove(int v) {
	if (lastButOneMove == v) {
		lastButOneMove = 0;
		speed = lastMove;
	} else if (lastMove == v) {
		if (lastButOneMove != 0) {
			speed = lastButOneMove;
			lastMove = lastButOneMove;
			lastButOneMove = 0;
		}
		else {
			lastMove = 0;
			speed = 0;
			/*
			int rest = x_position%Box::BOX_WIDTH;
			if(rest<10) {
				x_position -=rest;
			}
			else if(rest>(Box::BOX_WIDTH-10)) {
				x_position +=Box::BOX_WIDTH-rest-1;
			}
			*/
		}
	} else {
        // Nothing to do
    }
}

// -------------------------------------------------------------
// Function: getXPosition()
// Description:	Returns the current Jack's position on the X axis.
// Return: int
// -------------------------------------------------------------
int Jack::getXPosition() {
	return this->x_position;
}

// -------------------------------------------------------------
// Function: getYPosition()
// Description:	Returns the current Jack's position on the Y axis.
// Return: int
// -------------------------------------------------------------
int Jack::getYPosition() {
	return this->y_position;
}

// -------------------------------------------------------------
// Function: pushBox()
// Description:
// Return: void
// Observations:
// 		Funtion not implemented
// -------------------------------------------------------------
void Jack::pushBox() {
}

// -------------------------------------------------------------
// Function: setSpriteClips()
// Description: Initializes the dimensions of each picture frame and each Jack's moviment.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClips() {
    spriteClips[0].x = 0;
    spriteClips[0].y = JACK_HEIGHT;
    spriteClips[0].w = JACK_WIDTH;
    spriteClips[0].h = JACK_HEIGHT;

    spriteClips[1].x = JACK_WIDTH;
    spriteClips[1].y = JACK_HEIGHT;
    spriteClips[1].w = JACK_WIDTH;
    spriteClips[1].h = JACK_HEIGHT;

    spriteClips[2].x = JACK_WIDTH*2;
    spriteClips[2].y = JACK_HEIGHT;
    spriteClips[2].w = JACK_WIDTH;
    spriteClips[2].h = JACK_HEIGHT;

    spriteClips[3].x = JACK_WIDTH*3;
    spriteClips[3].y = JACK_HEIGHT;
    spriteClips[3].w = JACK_WIDTH;
    spriteClips[3].h = JACK_HEIGHT;

    spriteClips[4].x = JACK_WIDTH;
    spriteClips[4].y = 0;
    spriteClips[4].w = JACK_WIDTH;
    spriteClips[4].h = JACK_HEIGHT;

    spriteClips[5].x = JACK_WIDTH*2;
    spriteClips[5].y = 0;
    spriteClips[5].w = JACK_WIDTH;
    spriteClips[5].h = JACK_HEIGHT;

    spriteClips[6].x = JACK_WIDTH*3;
    spriteClips[6].y = 0;
    spriteClips[6].w = JACK_WIDTH;
    spriteClips[6].h = JACK_HEIGHT;

    spriteClips[7].x = JACK_WIDTH*4;
    spriteClips[7].y = JACK_HEIGHT;
    spriteClips[7].w = JACK_WIDTH;
    spriteClips[7].h = JACK_HEIGHT;

    spriteClips[8].x = JACK_WIDTH*4;
    spriteClips[8].y = 0;
    spriteClips[8].w = JACK_WIDTH;
    spriteClips[8].h = JACK_HEIGHT;
}
