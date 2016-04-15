#include "box.h"
#include "level.h"
#include "sdlutil.h"

using namespace std;

void Box::drawSelf(SDL_Surface * surface) {
    if (used == true) {
        SDLUtil::applySurface(this->x_position, this->y_position, this->box, surface);
    } else {
        // Nothing to do
    }
}

Box::Box(string filename) {
    this->box = SDLUtil::loadImage(filename);
    x_position = 0;
    y_position = 0;
    speed = 0;
    lyingDown = false;
    used = false;
}

Box::~Box() {
    if (box != NULL) {
        SDL_FreeSurface(box);
    } else {
        // Nothing to do
    }
        
}

int Box::getPositionX() {
    return this->x_position;
}

int Box::getPositionY() {
    return this->y_position;
}

int Box::getSpeed() {
    return this->speed;
}

void Box::setPosition(int x, int y) {
    this->x_position = x;
    this->y_position = y;
}

void Box::accelerate() {
}

void Box::fall(vector<Box*>grid[12]) {
    if (lyingDown == false) {
        speed += ACCELERATION;

        if (speed > MAX_SPEED) {
            speed = MAX_SPEED;
        } else {
            // Nothing to do
        }

        y_position += speed;
        if (y_position >= (int)(Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - 38 * 2 - (grid[(x_position - Level::LEVEL_X_OFFSET)/38].size()*38))) {
            speed = 0;
            lyingDown = true;
            y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - 38 * 2 - (grid[(x_position - Level::LEVEL_X_OFFSET)/38].size() * 38);
			grid[(x_position - Level::LEVEL_X_OFFSET)/38].push_back(this);
            //grid[(x_position - Level::LEVEL_X_OFFSET)/38]++;
        } else {
            // Nothing to do
        }
    }

    return;
}
