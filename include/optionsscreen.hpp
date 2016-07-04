#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "gameobject.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "sdlutil.hpp"
#include <string>

class OptionsScreen : public GameObject {
	void drawSelf(SDL_Surface *surface);
	
public:
    SDL_Surface * helpMessage;			// Surface for "Help" that will be applie on screen.
	SDL_Surface * optionsScreen;		// Surface for "Options" that will be applie on screen.
	
	OptionsScreen(std::string filename, std::string filenameHelp);
	~OptionsScreen();

	static const int SCREEN_WIDTH = 854;		// Size of width screen that will show the "Help" and "Options" of game.
	static const int SCREEN_HEIGHT = 480;		// Size of height screen that will show the "Help" and "Options" of game.
	/* data */
};
#endif