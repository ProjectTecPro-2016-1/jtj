#include "gameoverscreen.h"
#include "sdlutil.h"
#include <cassert>

using namespace std;

// -------------------------------------------------------------  
// Function: drawSelf()  
// Description: Draws the image on screen, according to the level.
// Parameters:
//		SDL_Surface * surface;		Is the surface that the image will load.
// Return: void  
// -------------------------------------------------------------  
void GameOverScreen::drawSelf(SDL_Surface * surface) {
    SDLUtil::applySurface(0, 0, this->gameOverScreen, surface);
    return;
}

// -------------------------------------------------------------  
// Function: GameOverScreen()  
// Description: Load the image of level on screen.
// Parameters:
//		string filename;		Name of a image file of level that will be showed on screen.
// Return: void  
// -------------------------------------------------------------  
GameOverScreen::GameOverScreen(string filename) {
    assert(filename != "" && "Fail to load image because image filename is empty.");
    this->gameOverScreen = SDLUtil::loadImage(filename);
}

// -------------------------------------------------------------  
// Function: ~GameOverScreen()  
// Description: Destructor of class that clean the screen.
// Return: void  
// -------------------------------------------------------------  
GameOverScreen::~GameOverScreen() {
    if (gameOverScreen != NULL) {
        SDL_FreeSurface(gameOverScreen);
    } else {
		// Nothing to do
	}
}