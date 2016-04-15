#ifndef INITSCREEN_H
#define INITSCREEN_H

#include "gameobject.h"
#include <string>

class InitScreen : public GameObject {
	void drawSelf(SDL_Surface *surface);
    
	SDL_Surface * initScreen;		// Keeps the image that loaded.
	
	public:
	
		InitScreen(std::string filename);
		~InitScreen();

        static const int LEVEL_WIDTH = 854;			// Size of width screen that will show the image level, in pixels.
        static const int LEVEL_HEIGHT = 480;		// Size of height screen that will show the image level, in pixels.
};

#endif
