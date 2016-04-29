#include "box.h"
#include "level.h"
#include "sdlutil.h"
#include <cassert>

using namespace std;

// -------------------------------------------------------------
// Function: drawSelf()
// Description: Draws the box in a specific screen position according to the box attributes.
// Parameters:
//		SDL_Surface * surface;		Pointer for the surface where the graphic component will be
//                                  drawn.
// Return: void
// -------------------------------------------------------------
void Box::drawSelf(SDL_Surface * surface) {
    assert(surface != NULL && "Can't draw box on screen");

    if (used == true) {
        SDLUtil::applySurface(this->x_position, this->y_position, this->box, surface);
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------
// Function: Box()
// Description: Box class builder where the inicialization of the class variables happen.
// Parameters:
//		string fileName;  		Box landscape file name.
// Return: void
// -------------------------------------------------------------
Box::Box(string filename) {
    assert(filename != NULL && "Can't load Box' image");

    this->box = SDLUtil::loadImage(filename);
    x_position = 0;
    y_position = 0;
    speed = 0;
    lyingDown = false;
    used = false;
}

// -------------------------------------------------------------
// Function: ~Box()
// Description: Box class destructor where the box image files free themselves.
// Return: void
// -------------------------------------------------------------
Box::~Box() {
    if (box != NULL) {
        SDL_FreeSurface(box);
    } else {
        // Nothing to do
    }

}

// -------------------------------------------------------------
// Function: getPositionX()
// Description: Returns a position in the box X axis at the right moment.
// Return: int
// -------------------------------------------------------------
int Box::getPositionX() {
    return this->x_position;
}

// -------------------------------------------------------------
// Function: getPositionY()
// Description: Returns a position in the box Y axis at the right moment.
// Return: int
// -------------------------------------------------------------
int Box::getPositionY() {
    return this->y_position;
}

// -------------------------------------------------------------
// Function: getSpeed()
// Description: Returns the speed which the box is moving at the right moment.
// Return: int
// -------------------------------------------------------------
int Box::getSpeed() {
    return this->speed;
}

// -------------------------------------------------------------
// Function: setPosition()
// Description: Return the speed which the box is moving at the right moment.
// Parameters:
//		int x;			Insert the value of axis X of the box on the attribute that keeps the
//                      information
//		int y;  		Insert the value of axis Y of the box on the attribute that keeps the
//                      information
// Return: void
// -------------------------------------------------------------
void Box::setPosition(int x, int y) {
    this->x_position = x;
    this->y_position = y;
}

// -------------------------------------------------------------
// Function: accelerate()
// Description: Increase the speed of the box at the right moment.
// Return: void
// Observations:
// 		- Funtion not implemented
// -------------------------------------------------------------
void Box::accelerate() {
}

// -------------------------------------------------------------
// Function: fall()
// Description: Control the box fall during the execution of the level of the game.
// Parameters:
//		int vector<Box*> grid[12];			Vector that contain the box positions in the platform.
// Return: void
// -------------------------------------------------------------
void Box::fall(vector<Box*>grid[12]) {
    if (lyingDown == false) {
        speed += ACCELERATION;

        if (speed > MAX_SPEED) {
            speed = MAX_SPEED;
        } else {
            // Nothing to do
        }

        int newYPosition = ((int)(Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - 38 * 2 -
                                (grid[(x_position - Level::LEVEL_X_OFFSET)/38].size()*38)));

        y_position += speed;
        if (y_position >= newYPosition) {
            speed = 0;
            lyingDown = true;

            y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - 38 * 2 -
                        (grid[(x_position - Level::LEVEL_X_OFFSET)/38].size() * 38);

            grid[(x_position - Level::LEVEL_X_OFFSET)/38].push_back(this);
            //grid[(x_position - Level::LEVEL_X_OFFSET)/38]++;
        } else {
            // Nothing to do
        }
    } else {
	// Nothing to do
    }

    return;
}
