#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "gameobject.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "sdlutil.h"
#include <string>

class OptionsScreen : public GameObject {
    SDL_Surface * helpMessage;			// Surface for "Help" that will be applie on screen.
	SDL_Surface * optionsScreen;		// Surface for "Options" that will be applie on screen.
	
	void drawSelf(SDL_Surface *surface);
	
public:
	
	OptionsScreen(std::string filename);
	~OptionsScreen();

	static const int SCREEN_WIDTH = 854;		// Size of width screen that will show the "Help" and "Options" of game.
	static const int SCREEN_HEIGHT = 480;		// Size of height screen that will show the "Help" and "Options" of game.
	/* data */
};
#endif