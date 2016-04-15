#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "gameobject.h"
#include <string>

class PauseScreen : public GameObject {
    SDL_Surface * pauseScreen;						// Surface for "Pause" that will be applie on screen.
    void drawSelf(SDL_Surface *surface);
    
	public:

        PauseScreen(std::string filename);
        ~PauseScreen();

        static const int LEVEL_WIDTH = 854;			// Size of width screen that will show the image level, in pixels.
        static const int LEVEL_HEIGHT = 480;		// Size of height screen that will show the image level, in pixels.
};

#endif