#include <cassert>
#include "label.h"
#include "sdlutil.h"
#include "level.h"

// -------------------------------------------------------------  
// Function: Label()  
// Description: Label class builder where the inicialization of the class variables happen.
// Parameters:
//		string filename;		Label landscape file name.
//		int xPosition;			Where the label is localizated in axis X.
//		int yPosition;			Where the label is localizated in axis Y.
// Return: void  
// -------------------------------------------------------------
Label::Label(std::string filename, int xPosition, int yPosition) {
	assert(filename != "" && "Impossible to loadImage, because the image filename of label is empty");
	assert(xPosition > 0 && "xPosition needs to be a positive value");
	assert(yPosition > 0 && "yPosition needs to be a positive value");	
	this->label = SDLUtil::loadImage(filename);
	this->xPosition = xPosition;
	this->yPosition = yPosition;
}

// -------------------------------------------------------------  
// Function: ~Label()  
// Description: Label class destructor where the level image files free themselves.
// Return: void  
// -------------------------------------------------------------
Label::~Label() {
	if (label != NULL) {
		SDL_FreeSurface(label);
	} else {
        // Nothing to do
    }
}

// -------------------------------------------------------------  
// Function: drawSelf()  
// Description: Draws the label on the specified surface.
// Parameters:
//		SDL_Surface * surface;		Pointer for the surface where the graphic component will be drawn.
// Return: void  
// -------------------------------------------------------------
void Label::drawSelf(SDL_Surface * surface) {
	SDLUtil::applySurface(this->xPosition, this->yPosition, this->label, surface);
}

// -------------------------------------------------------------  
// Function: wasClicked()  
// Description: Where was clicked by the user
// Parameters:
//		int xMouse;		Where the mouse is localizated in axis X.
//		int yMouse;		Where the mouse is localizated in axis Y.
// Return: bool
// -------------------------------------------------------------
bool Label::wasClicked(int xMouse, int yMouse) {
	if (xMouse > this->xPosition && xMouse < this->xPosition + LABEL_WIDTH && yMouse > this->yPosition && yMouse < this->yPosition + LABEL_HEIGHT) {
		return true;
	} else {
        // Nothing to do
    }

	return false;
}
