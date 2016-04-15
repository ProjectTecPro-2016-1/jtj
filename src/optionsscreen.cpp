#include "optionsscreen.h"
#include "sdlutil.h"

using namespace std;

// -------------------------------------------------------------  
// Function: drawSelf()  
// Description: Applies the image of "Help" and "Options" on screen.
// Parameters:
//		SDL_Surface *surface;		Is the surface that the image will load.
// Attributes: nothing
// Return: void  
// -------------------------------------------------------------  
void OptionsScreen::drawSelf(SDL_Surface *surface)
{
	SDLUtil::applySurface(0, 0, this->optionsScreen, surface);
	SDLUtil::applySurface(20, 100, this->helpMessage, surface);
	return ;
}

// -------------------------------------------------------------  
// Function: OptionsScreen()  
// Description: Load the image of "Help" and "Options".
// Parameters:
//		string filename;		Name of image file that will be showed on screen.
// Return: void  
// -------------------------------------------------------------  
OptionsScreen::OptionsScreen(string filename)
{
	this->optionsScreen = SDLUtil::loadImage(filename.c_str());
	this-> helpMessage = SDLUtil::loadImage("resources/helpTextImage.png");
}

// -------------------------------------------------------------  
// Function: ~OptionsScreen()  
// Description: Destructor of class that clean the screen of options and screen of help.
// Return: void  
// -------------------------------------------------------------  
OptionsScreen::~OptionsScreen()
{
	if (this->optionsScreen != NULL) {
		SDL_FreeSurface(this->optionsScreen);
	} else {
		// Nothing to do
	}
	if (this->helpMessage != NULL) {
		SDL_FreeSurface(this->helpMessage);
	} else {
		// Nothing to do
	}
}
