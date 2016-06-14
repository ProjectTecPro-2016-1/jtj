#include "pausescreen.hpp"
#include "sdlutil.hpp"
#include <cassert>

using namespace std;

// -------------------------------------------------------------  
// Function: drawSelf()  
// Description: Applies the image of Pause Game on screen.
// Parameters:
//		SDL_Surface *surface;		Is the surface that the image will load.
// Return: void  
// -------------------------------------------------------------  
void PauseScreen::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(0, 0, this->pauseScreen, surface);
    return;
}
  
// -------------------------------------------------------------  
// Function: PauseScreen()  
// Description: Load the image of Pause on game.
// Parameters:
//		string filename;		Name of "pause" image file that will be showed on screen.
// Return: void  
// -------------------------------------------------------------  
PauseScreen::PauseScreen(string filename) {
    assert(filename != "" && "Fail to load image because image filename is empty.");
    this->pauseScreen = SDLUtil::loadImage(filename);
}

// -------------------------------------------------------------  
// Function: ~PauseScreen()  
// Description: Destructor of class that clean the pause screen.
// Return: void  
// -------------------------------------------------------------
PauseScreen::~PauseScreen() {
    if (pauseScreen != NULL) {
        SDL_FreeSurface(pauseScreen);
    } else {
		// Nothing to do
	}
}