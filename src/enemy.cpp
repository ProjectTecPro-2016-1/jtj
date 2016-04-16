#include "enemy.h"
#include "level.h"
#include "sdlutil.h"
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
    if (moveDirection%2 == 0 && movesLeft > 0) {
        frame ++;

        if (frame > 3) {
            frame = 1;
        } else {
            // Nothing to do
        }
    } else if (moveDirection%2 == 1 && movesLeft > 0) {
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
    } else if (movesLeft == 0 && moveDirection > 30 && moveDirection < 40) {
        frame = 7;
    } else {
        frame = 0;
    }

    SDLUtil::applySurface(this->x_position, this->y_position, this->enemy, surface,
                         &spriteClips[frame]);
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
    this->x_position = Level::LEVEL_X_OFFSET + 38;
    this->y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET -
                        Enemy::ENEMY_HEIGHT - 38 * 8 - 1;
    movesLeft = 0;
    moveDirection = 0;
    srand((unsigned)time(0));
    frame = 0;
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
    if (movesLeft > 0 && moveDirection%2 == 0) {
        x_position += 2;
        movesLeft -= 2;
    } else if(movesLeft > 0 && moveDirection % 2 == 1) {
        x_position -= 2;
        movesLeft -= 2;
    } else {
        // Nothing to do
    }

    if (x_position <= Level::LEVEL_X_OFFSET) {
        x_position += 2;
        movesLeft = 36;
        moveDirection = 2;
    } else {
        // Nothing to do
    }

    if (x_position >= Level::LEVEL_X_OFFSET + Level::LEVEL_WIDTH - 38) {
        x_position -= 2;
        movesLeft = 36;
        moveDirection = 1;
    } else {
        // Nothing to do
    }


    if (movesLeft <= 0) {
        //delay
        if (moveDirection > 0) {
            moveDirection--;
            // descomentar em caso de erro return;
        } else {
            //gen  movesLeft and moveDirection
            movesLeft = (rand() % 6) * 38;
            moveDirection = (rand() % 120);
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
    if ((x_position-Level::LEVEL_X_OFFSET) % 38 == 0) {
        if (movesLeft == 0 && moveDirection == 30) {
            for (unsigned int i = 0; i < boxes.size(); i++) {
                if (boxes.at(i)->used == false) {
                    boxes.at(i)->used = true;
                    boxes.at(i)->setPosition(x_position, y_position - Enemy::ENEMY_HEIGHT +
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
