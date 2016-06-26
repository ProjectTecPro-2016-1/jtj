#include "enemy.hpp"
#include "level.hpp"
#include "sdlutil.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

// -------------------------------------------------------------
// Function: drawSelf()
// Description: Selects the current motion frame and draws the enemies image in specific position
//				on the screen according to the enemy attributes.
// Parameters:
//		SDL_Surface * surface;  		Pointer for surface where the graphic component will be
//                                      drawn.
// Return: void
// -------------------------------------------------------------
void Enemy::drawSelf(SDL_Surface * surface) {
    //SDLUtil::applySurface(this->x_position, this->y_position, this->enemy, surface);
    if (getMoveDirection() % 2 == 0 && getMovesLeft() > 0) {
        setFrame(getFrame() + 1);

        if (getFrame() > 3) {
            setFrame(1); 
        } else {
            // Nothing to do
        }
    } else if (getMoveDirection() % 2 == 1 && getMovesLeft() > 0) {
        setFrame(getFrame() + 1);

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
    } else if (getMovesLeft() == 0 && getMoveDirection() > 30 && getMoveDirection() < 40) {
        setFrame(7);
    } else {
        setFrame(0);
    }

    SDLUtil::applySurface(getXPosition(), getYPosition(), this->enemy, surface,
                         &spriteClips[getFrame()]);
    return;
}

// -------------------------------------------------------------
// Function: setSpriteClips()
// Description: Initializes the dimensions of each picture frame and each enemy moviment.
// Return: void
// -------------------------------------------------------------
void Enemy::setSpriteClips() {
    spriteClips[0].x = 0;
    spriteClips[0].y = ENEMY_HEIGHT;
    spriteClips[0].w = ENEMY_WIDTH;
    spriteClips[0].h = ENEMY_HEIGHT;

    spriteClips[1].x = ENEMY_WIDTH;
    spriteClips[1].y = ENEMY_HEIGHT;
    spriteClips[1].w = ENEMY_WIDTH;
    spriteClips[1].h = ENEMY_HEIGHT;

    spriteClips[2].x = ENEMY_WIDTH*2;
    spriteClips[2].y = ENEMY_HEIGHT;
    spriteClips[2].w = ENEMY_WIDTH;
    spriteClips[2].h = ENEMY_HEIGHT;

    spriteClips[3].x = ENEMY_WIDTH*3;
    spriteClips[3].y = ENEMY_HEIGHT;
    spriteClips[3].w = ENEMY_WIDTH;
    spriteClips[3].h = ENEMY_HEIGHT;

    spriteClips[4].x = ENEMY_WIDTH;
    spriteClips[4].y = 0;
    spriteClips[4].w = ENEMY_WIDTH;
    spriteClips[4].h = ENEMY_HEIGHT;

    spriteClips[5].x = ENEMY_WIDTH*2;
    spriteClips[5].y = 0;
    spriteClips[5].w = ENEMY_WIDTH;
    spriteClips[5].h = ENEMY_HEIGHT;

    spriteClips[6].x = ENEMY_WIDTH*3;
    spriteClips[6].y = 0;
    spriteClips[6].w = ENEMY_WIDTH;
    spriteClips[6].h = ENEMY_HEIGHT;

    spriteClips[7].x = ENEMY_WIDTH*4;
    spriteClips[7].y = ENEMY_HEIGHT;
    spriteClips[7].w = ENEMY_WIDTH;
    spriteClips[7].h = ENEMY_HEIGHT;
}

// -------------------------------------------------------------
// Function: Enemy()
// Description: Enemy class builder where the initializations of the variables happen.
// Parameters:
//		string fileName;  		Enemy landscape file name.
// Return: void
// -------------------------------------------------------------
Enemy::Enemy(string filename) {
    this->enemy = SDLUtil::loadImage(filename);
    setXPosition(Level::LEVEL_X_OFFSET + 38);
    setYPosition(Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET -
                        Enemy::ENEMY_HEIGHT - 38 * 8 - 1);
    setMovesLeft(0);
    setMoveDirection(0);
    srand((unsigned)time(0));
    setFrame(0);
}

// -------------------------------------------------------------
// Function: ~Enemy()
// Description: Enemy class destructor where the landscape image files free themselves.
// Return: void
// -------------------------------------------------------------
Enemy::~Enemy() {
    if (enemy != NULL) {
        SDL_FreeSurface(enemy);
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------
// Function: move()
// Description: Moves the enemy horizontally according to level dimensions.
// Return: void
// -------------------------------------------------------------
void Enemy::move() {
    // Change of position according to MovesLeft and MoveDirection
    if (getMovesLeft() > 0 && getMoveDirection() % 2 == 0) {
        setXPosition(getXPosition() + 2);
        setMovesLeft(getMovesLeft() - 2);
    } else if(getMovesLeft() > 0 && getMoveDirection() % 2 == 1) {
        setXPosition(getXPosition() - 2);
        setMovesLeft(getMovesLeft() - 2);
    } else {
        // Nothing to do
    }

    if (getXPosition() <= Level::LEVEL_X_OFFSET) {
        setXPosition(getXPosition() + 2);
        setMovesLeft(36);
        setMoveDirection(2);
    } else {
        // Nothing to do
    }

    if (getXPosition() >= Level::LEVEL_X_OFFSET + Level::LEVEL_WIDTH - 38) {
        setXPosition(getXPosition() - 2);
        setMovesLeft(36);
        setMoveDirection(1);
    } else {
        // Nothing to do
    }

    // Fifth
    if (getMovesLeft() <= 0) {
        //delay
        if (getMoveDirection() > 0) {
            setMoveDirection(getMoveDirection() - 1);
        // Sixth
        } else {
            //gen  movesLeft and moveDirection
            setMovesLeft((rand() % 6) * 38);
            setMoveDirection(rand() % 120);
        }
    } else {
        // Nothing to do
    }

    return;
}

// -------------------------------------------------------------
// Function: throwBox()
// Description: Controls the enemies freedom box when the right position is achieved.
// Parameters:
//		int vector<Box*> boxes;			Vector that contains boxes it´s positions.
// Return: void
// -------------------------------------------------------------
void Enemy::throwBox(vector<Box*> boxes) {
    if ((getXPosition() - Level::LEVEL_X_OFFSET) % 38 == 0) {
        if (getMovesLeft() == 0 && getMoveDirection() == 30) {
            for (unsigned int i = 0; i < boxes.size(); i++) {
                if (boxes.at(i)->used == false) {
                    boxes.at(i)->used = true;
                    boxes.at(i)->setPosition(getXPosition(), getYPosition() - Enemy::ENEMY_HEIGHT +
                                            Box::BOX_HEIGHT);
                    break;// descomentar em caso de erro return;
                } else {
                    // Nothing to do
                }
            }
        } else {
            // Nothing to do
        }
    } else {
        // Nothing to do
    }

    return;
}

void Enemy::setXPosition(int xPosition) {
    this->xPosition =  xPosition;
}

int Enemy::getXPosition() {
    return this->xPosition;
}

void Enemy::setYPosition(int yPosition) {
    this->yPosition =  yPosition;
}

int Enemy::getYPosition() {
    return this->yPosition;
}

void Enemy::setMovesLeft(int movesLeft) {
    this->movesLeft =  movesLeft;
}

int Enemy::getMovesLeft() {
    return this->movesLeft;
}

void Enemy::setMoveDirection(int moveDirection) {
    this->moveDirection =  moveDirection;
}

int Enemy::getMoveDirection() {
    return this->moveDirection;
}

void Enemy::setFrame(int frame) {
    this->frame =  frame;
}

int Enemy::getFrame() {
    return this->frame;
}
        