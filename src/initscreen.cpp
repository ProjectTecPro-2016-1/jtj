#include "initscreen.h"
#include "sdlutil.h"

using namespace std;
	
// -------------------------------------------------------------  
// Function: drawSelf()  
// Description: Applies the image of Start Game on screen.
// Parameters:
//		SDL_Surface *surface;		Is the surface that the image will load.
// Return: void  
// -------------------------------------------------------------  
void InitScreen::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(0, 0, this->initScreen, surface);
    return;
}

// -------------------------------------------------------------  
// Function: InitScreen()  
// Description: Load the image of Start Game, the initial screen.
// Parameters:
//		string filename;		Name of "initial" image file that will be showed on screen.
// Return: void  
// -------------------------------------------------------------
InitScreen::InitScreen(string filename) {
    this->initScreen = SDLUtil::loadImage(filename);
}

// -------------------------------------------------------------  
// Function: ~InitScreen()  
// Description: Destructor of class that clean the initial screen.
// Return: void  
// -------------------------------------------------------------  
InitScreen::~InitScreen() {
    if (initScreen != NULL) {
        SDL_FreeSurface(initScreen);
    } else {
		// Nothing to do
	}
}