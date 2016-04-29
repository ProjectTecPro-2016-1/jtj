#include <cassert>
#include "level.h"
#include "sdlutil.h"

using namespace std;

// -------------------------------------------------------------  
// Function: Level()  
// Description: Level class builder where the inicialization of the class variables happen.
// Parameters:
//		string filename;		Level landscape file name.
// Return: void  
// -------------------------------------------------------------  
Level::Level(string filename) {
	assert(filename != "" && "Impossible to loadImage, because the image filename of level is empty");    
	this->level = SDLUtil::loadImage(filename);
	//for(unsigned int i = 0; i < sizeof(grid)/sizeof(int); i++) {
	//    grid[i] = 0;
    	//}
}

// -------------------------------------------------------------  
// Function: ~Level()  
// Description: Level class destructor where the level image files free themselves.
// Return: void  
// -------------------------------------------------------------  
Level::~Level() {
    	if (level != NULL) {
    	    SDL_FreeSurface(level);
    	} else {
    	    // Nothing to do
    	}
}

// -------------------------------------------------------------  
// Function: drawSelf()  
// Description: Draws the level on the specified surface.
// Parameters:
//		SDL_Surface *surface;		Pointer for the surface where the graphic component will be drawn.
// Return: void  
// -------------------------------------------------------------
void Level::drawSelf(SDL_Surface * surface) {
    	SDLUtil::applySurface(Level::LEVEL_X_OFFSET, Level::LEVEL_Y_OFFSET, this->level, surface);
    	return;
}

// -------------------------------------------------------------  
// Function: getBoxes()  
// Description: Returns a vector whith all box positions.
// Return: vector<Box*>  
// -------------------------------------------------------------
vector<Box*> Level::getBoxes() {
	return boxes;
}
