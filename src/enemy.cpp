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
    // FirstFrame
    if (getMoveDirection() % 2 == 0 && getMovesLeft() > 0) {
        setFrame(getFrame() + 1);

        if (getFrame() > 3) {
            setFrame(1); 
        } else {
            // Nothing to do
        }
    // SecondFrame
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
    // ThirdFrame
    } else if (getMovesLeft() == 0 && getMoveDirection() > 30 && getMoveDirection() < 40) {
        setFrame(7);
    // FourthFrame
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
    setStopEnemy();
    setStartingtRightEnemyMovement();
    setContinuingRightEnemyMovement();
    setFinishingRightEnemyMovement();
    setFinishingLeftEnemyMovement();
    setContinuingLeftEnemyMovement();
    setStartingtLeftEnemyMovement();
    setDropBox();
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
    if (getMovesLeft() > 0 && getMoveDirection() % 2 == 0) {
        FirstMove();
    } else if(getMovesLeft() > 0 && getMoveDirection() % 2 == 1) {
        SecondMove();    
    } else {
        // Nothing to do
    }

    if (getXPosition() <= Level::LEVEL_X_OFFSET) {
        ThirdMove();
    } else {
        // Nothing to do
    }

    if (getXPosition() >= Level::LEVEL_X_OFFSET + Level::LEVEL_WIDTH - 38) {
        FourthMove();
    } else {
        // Nothing to do
    }

    if (getMovesLeft() <= 0) {
        //delay
        if (getMoveDirection() > 0) {
            FifthMove();
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
                    setBox(boxes, i);                
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

void Enemy::setBox(vector<Box*> boxes, int i){
    boxes.at(i)->used = true;
    boxes.at(i)->setPosition(getXPosition(), getYPosition() - Enemy::ENEMY_HEIGHT +
                                            Box::BOX_HEIGHT);
}

// -------------------------------------------------------------
// Function: setStopEnemy()
// Description: Initializes the dimensions of finishing movement to right of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::setStopEnemy() {
    spriteClips[0].x = 0;
    spriteClips[0].y = ENEMY_HEIGHT;
    spriteClips[0].w = ENEMY_WIDTH;
    spriteClips[0].h = ENEMY_HEIGHT;    
}


// -------------------------------------------------------------
// Function: setStartingtRightEnemyMovement()
// Description: Initializes the dimensions of starting movement to right of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::setStartingtRightEnemyMovement() {
    spriteClips[1].x = ENEMY_WIDTH;
    spriteClips[1].y = ENEMY_HEIGHT;
    spriteClips[1].w = ENEMY_WIDTH;
    spriteClips[1].h = ENEMY_HEIGHT;
}

// -------------------------------------------------------------
// Function: setContinuingRightEnemyMovement()
// Description: Initializes the dimensions of continuing movement to right of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::setContinuingRightEnemyMovement() {
    spriteClips[2].x = ENEMY_WIDTH*2;
    spriteClips[2].y = ENEMY_HEIGHT;
    spriteClips[2].w = ENEMY_WIDTH;
    spriteClips[2].h = ENEMY_HEIGHT;    
}

// -------------------------------------------------------------
// Function: setFinishingRightEnemyMovement()
// Description: Initializes the dimensions of finishing movement to right of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::setFinishingRightEnemyMovement() {
    spriteClips[3].x = ENEMY_WIDTH*3;
    spriteClips[3].y = ENEMY_HEIGHT;
    spriteClips[3].w = ENEMY_WIDTH;
    spriteClips[3].h = ENEMY_HEIGHT;
}

// -------------------------------------------------------------
// Function: setFinishingtLeftEnemyMovement()
// Description: Initializes the dimensions of finishing movement to left of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::setFinishingLeftEnemyMovement() {
    spriteClips[4].x = ENEMY_WIDTH;
    spriteClips[4].y = 0;
    spriteClips[4].w = ENEMY_WIDTH;
    spriteClips[4].h = ENEMY_HEIGHT;    
}

// -------------------------------------------------------------
// Function: setContinuingtLeftEnemyMovement()
// Description: Initializes the dimensions of continuing movement to left of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::setContinuingLeftEnemyMovement() {
    spriteClips[5].x = ENEMY_WIDTH*2;
    spriteClips[5].y = 0;
    spriteClips[5].w = ENEMY_WIDTH;
    spriteClips[5].h = ENEMY_HEIGHT;    
}

// -------------------------------------------------------------
// Function: setStartingtLeftEnemyMovement()
// Description: Initializes the dimensions of starting movement to left of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::setStartingtLeftEnemyMovement() {
    spriteClips[6].x = ENEMY_WIDTH*3;
    spriteClips[6].y = 0;
    spriteClips[6].w = ENEMY_WIDTH;
    spriteClips[6].h = ENEMY_HEIGHT;
}

// -------------------------------------------------------------
// Function: setDropBox()
// Description: Initializes the dimensions of finishing movement to right of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::setDropBox() {    
    spriteClips[7].x = ENEMY_WIDTH*4;
    spriteClips[7].y = ENEMY_HEIGHT;
    spriteClips[7].w = ENEMY_WIDTH;
    spriteClips[7].h = ENEMY_HEIGHT;
}

// -------------------------------------------------------------
// Function: FirstMove()
// Description: Make a movement according to the value of 
//              MovesLeft and MoveDirection of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::FirstMove() {
    setXPosition(getXPosition() + 2);
    setMovesLeft(getMovesLeft() - 2);
}

// -------------------------------------------------------------
// Function: SecondMove()
// Description: Make a movement according to the value of 
//              MovesLeft and MoveDirection of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::SecondMove() {
    setXPosition(getXPosition() - 2);
    setMovesLeft(getMovesLeft() - 2);
}

// -------------------------------------------------------------
// Function: ThirdMove()
// Description: Make a movement according to the position of 
//              enemy on x axis.
// Return: void
// -------------------------------------------------------------
void Enemy::ThirdMove() {
    setXPosition(getXPosition() + 2);
    setMovesLeft(36);
    setMoveDirection(2);
}

// -------------------------------------------------------------
// Function: FourthMove()
// Description: Make another movement according to value of
//              position of enemy on x axis.
// Return: void
// -------------------------------------------------------------
void Enemy::FourthMove() {
    setXPosition(getXPosition() - 2);
    setMovesLeft(36);
    setMoveDirection(1);
}

// -------------------------------------------------------------
// Function: FifthMove()
// Description: Make a movement according to value of
//              MovesLeft of enemy.
// Return: void
// -------------------------------------------------------------
void Enemy::FifthMove() {
    setMoveDirection(getMoveDirection() - 1);
}

// -------------------------------------------------------------
// Function: setXPosition()
// Description: Defines the enemy position in relation to the x axis. 
// Parameters:
//      int xPosition;         Enemy posistion on x axis.
// Return: void
// -------------------------------------------------------------
void Enemy::setXPosition(int xPosition) {
    this->xPosition =  xPosition;
}

// -------------------------------------------------------------
// Function: getXPosition()
// Description: Return the enemy position in relation to the x axis. 
// Return: int xPosition;   Enemy posistion on x axis.
// -------------------------------------------------------------
int Enemy::getXPosition() {
    return this->xPosition;
}

// -------------------------------------------------------------
// Function: setYPosition()
// Description: Defines the enemy position in relation to the y axis. 
// Parameters:
//      int yPosition;         Enemy posistion on y axis.
// Return: void
// -------------------------------------------------------------
void Enemy::setYPosition(int yPosition) {
    this->yPosition =  yPosition;
}

// -------------------------------------------------------------
// Function: getYPosition()
// Description: Return the enemy position in relation to the y axis. 
// Return: int yPosition;   Enemy posistion on y axis.
// -------------------------------------------------------------
int Enemy::getYPosition() {
    return this->yPosition;
}

// -------------------------------------------------------------
// Function: setMovesLeft()
// Description: Defines the enemy left position. 
// Parameters:
//      int movesLeft;      Value of left position of enemy.   
// Return: void
// -------------------------------------------------------------
void Enemy::setMovesLeft(int movesLeft) {
    this->movesLeft =  movesLeft;
}

// -------------------------------------------------------------
// Function: getMovesLeft()
// Description: Return the enemy left position. 
// Return:  int movesLeft;      Value of left position of enemy.   
// -------------------------------------------------------------
int Enemy::getMovesLeft() {
    return this->movesLeft;
}

// -------------------------------------------------------------
// Function: setMoveDirection()
// Description: Defines the direction of enemy. 
// Parameters:
//      int moveDirection;      Value of direction of enemy.   
// Return: void
// -------------------------------------------------------------
void Enemy::setMoveDirection(int moveDirection) {
    this->moveDirection =  moveDirection;
}

// -------------------------------------------------------------
// Function: getMoveDirection()
// Description: Return the enemy direction. 
// Return:  int movesDirection;      Value of direction of enemy.   
// -------------------------------------------------------------
int Enemy::getMoveDirection() {
    return this->moveDirection;
}

// -------------------------------------------------------------
// Function: setFrame()
// Description: Defines defines which frame the enemy is.
// Parameters:
//      int frame;      Frame value that enemy is.  
// Return: void
// -------------------------------------------------------------
void Enemy::setFrame(int frame) {
    this->frame =  frame;
}

// -------------------------------------------------------------
// Function: getFrame()
// Description: Return which frame the enemy is.
// Return:  int frame;      Frame value that enemy is.  
// -------------------------------------------------------------
int Enemy::getFrame() {
    return this->frame;
}