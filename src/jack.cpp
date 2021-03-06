#include "jack.hpp"
#include "level.hpp"
#include "sdlutil.hpp"

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
    setXPosition(JACK_WIDTH + Level::LEVEL_X_OFFSET);
    setYPosition(Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - Jack::JACK_HEIGHT - 38);
    setSpeed(0);
    setDead(false);
    setVerticalSpeed(0);
    setJumping(false);
    setLastMove(0);
    setLastButOneMove(0);
    setStrength(0);
    setFrame(0);
}

// -------------------------------------------------------------
// Function: ~Jack()
// Description: Jack class destructor in which images files free themselves.
// Return: void
// -------------------------------------------------------------
Jack::~Jack() {
    if (jack != NULL) {
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
    setDead(true);
}

// -------------------------------------------------------------
// Function: isDead()
// Description:	Return the boolean variable indicating whether Jack is dead or not.
// Return: bool
// -------------------------------------------------------------
bool Jack::isDead() {
    return getDead();
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

    if (value < limit1) {
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
    if (getJumping() == true) {
        if(getSpeed() >= 0) {
            setFrame(7);
        } else {
            setFrame(8);
        }
    } else if (getSpeed() > 0) {
        setFrame(getFrame() + 1);

        if (getFrame() > 3) {
            setFrame(1);
        } else {
            // Nothing to do
        }
    } else if (getSpeed() < 0) {
        setFrame(getFrame() +1);

        if (getFrame() < 4) {
            setFrame(4);
        } else {
            // Nothing to do
        }

        if (getFrame() > 6) {
            setFrame(4);
        } else {
            // Nothing to do
        }
    } else {
        setFrame(0);
    }

    SDLUtil::applySurface(getXPosition(), getYPosition(), this->jack, surface, &spriteClips[getFrame()]);
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
    setXPosition(getXPosition() + getSpeed());

    setXPosition(setLimit(getXPosition(), xBegin, xRange - JACK_WIDTH));
    setYPosition(setLimit(getYPosition(), yBegin, yRange - JACK_HEIGHT - 38));

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
void Jack::jump(Level * level) {

    setYPosition(getYPosition() + getVerticalSpeed());
    setVerticalSpeed(getVerticalSpeed() + ACCELERATION);

    int maxJumpHeightLeft = 0;
    maxJumpHeightLeft = calculatesMaxJumpHeightLeft(level);

    int maxJumpHeightRight = 0;
    maxJumpHeightRight = calculatesMaxJumpHeightRight(level);

    controlsMaxJump1(maxJumpHeightLeft, maxJumpHeightRight);
    controlsMaxJump2(maxJumpHeightLeft, maxJumpHeightRight);

    return;
}

// -------------------------------------------------------------
// Function: calculatesMaxJumpHeightLeft()
// Description: Calculates Jack's max jump height left.
// Parameters:
//                      Level * level;          Pointer to access level class.
// Return: int
// -------------------------------------------------------------
int Jack::calculatesMaxJumpHeightLeft(Level * level) {
    return (int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 - 38 -
                    (level->grid[(getXPosition() - Level::LEVEL_X_OFFSET) / 38].size() * 38));
}

// -------------------------------------------------------------
// Function: calculatesMaxJumpHeightRight()
// Description: Calculates Jack's max jump height right.
// Parameters:
//                      Level * level;          Pointer to access level class.
// Return: int
// -------------------------------------------------------------
int Jack::calculatesMaxJumpHeightRight(Level * level) {
    return (int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 - 38 -
                    (level->grid[(getXPosition() + 37 - Level::LEVEL_X_OFFSET) / 38].size() * 38));
}

// -------------------------------------------------------------
// Function: controlsMaxJump1()
// Description: Controls Jack's max jump.
// Parameters:
//                      int maxJumpHeightLeft;
//                      int maxJumpHeightRight;
// Return: void
// -------------------------------------------------------------
void Jack::controlsMaxJump1(int maxJumpHeightLeft, int maxJumpHeightRight) {
    if (getJumping() == true) {
        if ((getYPosition() >= maxJumpHeightLeft) || (getYPosition() >= maxJumpHeightRight)) {
            setJumping(false);
            setVerticalSpeed(1);
        } else {
            // Nothing to do
        }
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------
// Function: controlsMaxJump2()
// Description: Controls Jack's max jump.
// Parameters:
//                      int maxJumpHeightLeft;
//                      int maxJumpHeightRight;
// Return: void
// -------------------------------------------------------------
void Jack::controlsMaxJump2(int maxJumpHeightLeft, int maxJumpHeightRight) {
    //these next two if's handles boxes superior colision.
    if (getYPosition() >= maxJumpHeightLeft) {
        setYPosition(maxJumpHeightLeft);
        setVerticalSpeed(1);

    } else if (getYPosition() >= maxJumpHeightRight) {
        setYPosition(maxJumpHeightRight);
        setVerticalSpeed(1);

    } else { //this avoids double jumping while falling from a box
        setJumping(true);
    }
    //verticalSpeed++;
}

// -------------------------------------------------------------
// Function: pushMove()
// Description: Method that makes Jack move again after pausing.
// Parameters:
//		int v;		Variable that will make Jack walk again.
// Return: void
// -------------------------------------------------------------
void Jack::pushMove(int v) {
	if (getLastMove() == 0) {
		setSpeed(v);
		setLastMove(v);
	} else if (getLastButOneMove() == 0) {
		setSpeed(v);
		setLastButOneMove(v);
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
	if (getLastButOneMove() == v) {
		setLastButOneMove(0);
		setSpeed(getLastMove());
	} else if (getLastMove() == v) {
		if (getLastButOneMove() != 0) {
			setSpeed(getLastButOneMove());
			setLastMove(getLastButOneMove());
			setLastButOneMove(0);
		} else {
			setLastMove(0);
			setSpeed(0);
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
// Function: pushBox()
// Description:
// Return: void
// Observations:
// 		Funtion not implemented
// -------------------------------------------------------------
void Jack::pushBox() {
}

// -------------------------------------------------------------
// Function: setSpriteClipsStopped()
// Description: Sets Jack image stopped.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsStopped() {
    spriteClips[0].x = 0;
    spriteClips[0].y = JACK_HEIGHT;
    spriteClips[0].w = JACK_WIDTH;
    spriteClips[0].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClipsOneRight()
// Description: Sets Jack image to right.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsOneRight() {
    spriteClips[1].x = JACK_WIDTH;
    spriteClips[1].y = JACK_HEIGHT;
    spriteClips[1].w = JACK_WIDTH;
    spriteClips[1].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClipsSecondRight()
// Description: Sets Jack image to right.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsSecondRight() {
    spriteClips[2].x = JACK_WIDTH*2;
    spriteClips[2].y = JACK_HEIGHT;
    spriteClips[2].w = JACK_WIDTH;
    spriteClips[2].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClipsThirdRight()
// Description: Sets Jack image to right.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsThirdRight() {
    spriteClips[3].x = JACK_WIDTH*3;
    spriteClips[3].y = JACK_HEIGHT;
    spriteClips[3].w = JACK_WIDTH;
    spriteClips[3].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClipsJumpRight()
// Description: Sets Jack image jump to right.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsJumpRight() {
    spriteClips[7].x = JACK_WIDTH*4;
    spriteClips[7].y = JACK_HEIGHT;
    spriteClips[7].w = JACK_WIDTH;
    spriteClips[7].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClipsOneLeft()
// Description: Sets Jack image to left.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsOneLeft() {
    spriteClips[4].x = JACK_WIDTH;
    spriteClips[4].y = 0;
    spriteClips[4].w = JACK_WIDTH;
    spriteClips[4].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClipsSecondLeft()
// Description: Sets Jack image to left.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsSecondLeft() {
    spriteClips[5].x = JACK_WIDTH*2;
    spriteClips[5].y = 0;
    spriteClips[5].w = JACK_WIDTH;
    spriteClips[5].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClipsThirdLeft()
// Description: Sets Jack image to left.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsThirdLeft() {
    spriteClips[6].x = JACK_WIDTH*3;
    spriteClips[6].y = 0;
    spriteClips[6].w = JACK_WIDTH;
    spriteClips[6].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClipsJumpLeft()
// Description: Sets Jack image jump to left.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClipsJumpLeft() {
    spriteClips[8].x = JACK_WIDTH*4;
    spriteClips[8].y = 0;
    spriteClips[8].w = JACK_WIDTH;
    spriteClips[8].h = JACK_HEIGHT;
}

// -------------------------------------------------------------
// Function: setSpriteClips()
// Description: Initializes the dimensions of each picture frame and each Jack's moviment.
// Return: void
// -------------------------------------------------------------
void Jack::setSpriteClips() {
    setSpriteClipsStopped();
    setSpriteClipsOneRight();
    setSpriteClipsSecondRight();
    setSpriteClipsThirdRight();
    setSpriteClipsJumpRight();
    setSpriteClipsOneLeft();
    setSpriteClipsSecondLeft();
    setSpriteClipsThirdLeft();
    setSpriteClipsJumpLeft();
}

// -------------------------------------------------------------
// Function: getXPosition()
// Description: Returns the current Jack's position on the X axis.
// Return: int
// -------------------------------------------------------------
int Jack::getXPosition() {
    return this->x_position;
}

// -------------------------------------------------------------
// Function: setXPosition()
// Description: Return the Jack's position on the X axis.
// Parameters:
//      int x_position;          Insert the value of axis X of jack on the attribute that keeps the
//                                        information
// Return: void
// -------------------------------------------------------------
void Jack::setXPosition(int x_position) {
    this->x_position =  x_position;
}

// -------------------------------------------------------------
// Function: getYPosition()
// Description: Returns the current Jack's position on the Y axis.
// Return: int
// -------------------------------------------------------------
int Jack::getYPosition() {
    return this->y_position;
}

// -------------------------------------------------------------
// Function: setYPosition()
// Description: Return the Jack's position on the Y axis.
// Parameters:
//      int y_position;          Insert the value of axis Y of jack on the attribute that keeps the
//                                        information
// Return: void
// -------------------------------------------------------------
void Jack::setYPosition(int y_position) {
    this->y_position =  y_position;
}

// -------------------------------------------------------------
// Function: getSpeed()
// Description: Return the Jack's speed.
// Return: int
// -------------------------------------------------------------
int Jack::getSpeed() {
    return this->speed;
}

// -------------------------------------------------------------
// Function: setSpeed()
// Description: Return Jack's speed.
// Parameters:
//      int speed;
// Return: void
// -------------------------------------------------------------
void Jack::setSpeed(int speed) {
    this->speed =  speed;
}

// -------------------------------------------------------------
// Function: getDead()
// Description: Return dead Jack.
// Return: bool
// -------------------------------------------------------------
bool Jack::getDead() {
    return this->dead;
}

// -------------------------------------------------------------
// Function: setDead()
// Description: Return dead Jack.
// Parameters:
//      bool dead;
// Return: void
// -------------------------------------------------------------
void Jack::setDead(bool dead) {
    this->dead = dead;
}

// -------------------------------------------------------------
// Function: getVerticalSpeed()
// Description: Return vertical speed of Jack.
// Return: void
// -------------------------------------------------------------
int Jack::getVerticalSpeed() {
    return this->verticalSpeed;
}

// -------------------------------------------------------------
// Function: setVerticalSpeed()
// Description: Return vertical speed of Jack.
// Parameters:
//      int verticalSpeed;
// Return: void
// -------------------------------------------------------------
void Jack::setVerticalSpeed(int verticalSpeed) {
    this->verticalSpeed = verticalSpeed;
}

// -------------------------------------------------------------
// Function: getJumping()
// Description: Return Jack jumping.
// Return: void
// -------------------------------------------------------------
bool Jack::getJumping() {
    return this->jumping;
}

// -------------------------------------------------------------
// Function: setJumping()
// Description: Return Jack jumping.
// Parameters:
//      bool jumping;
// Return: void
// -------------------------------------------------------------
void Jack::setJumping(bool jumping) {
    this->jumping = jumping;
}

// -------------------------------------------------------------
// Function: getLastMove()
// Description: Return Jack's last move.
// Return: void
// -------------------------------------------------------------
int Jack::getLastMove() {
    return this->lastMove;
}

// -------------------------------------------------------------
// Function: setLastMove()
// Description: Return Jack's last move.
// Parameters:
//      int lastMove;
// Return: void
// -------------------------------------------------------------
void Jack::setLastMove(int lastMove) {
    this->lastMove = lastMove;
}

// -------------------------------------------------------------
// Function: getLastButOneMove()
// Description: Return Jack's last but one move.
// Return: void
// -------------------------------------------------------------
int Jack::getLastButOneMove() {
    return this->lastButOneMove;
}

// -------------------------------------------------------------
// Function: setLastButOneMove()
// Description: Return Jack's last but one move.
// Parameters:
//      int lastButOneMove;
// Return: void
// -------------------------------------------------------------
void Jack::setLastButOneMove(int lastButOneMove) {
    this->lastButOneMove = lastButOneMove;
}

// -------------------------------------------------------------
// Function: getStrength()
// Description: Return Jack's strength.
// Return: void
// -------------------------------------------------------------
int Jack::getStrength() {
    return this->strength;
}

// -------------------------------------------------------------
// Function: setStrength()
// Description: Return Jack's strength.
// Parameters:
//      int strength;
// Return: void
// -------------------------------------------------------------
void Jack::setStrength(int strength) {
    this->strength = strength;
}

// -------------------------------------------------------------
// Function: getFrame()
// Description: Return frame of Jack.
// Return: void
// -------------------------------------------------------------
int Jack::getFrame() {
    return this->frame;
}

// -------------------------------------------------------------
// Function: setFrame()
// Description: Return frame of Jack.
// Parameters:
//      int frame;
// Return: void
// -------------------------------------------------------------
void Jack::setFrame(int frame) {
    this->frame = frame;
}
