#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "gameobject.hpp"
#include <string>

class GameOverScreen : public GameObject {
    void drawSelf(SDL_Surface * surface);

    public:

        SDL_Surface * gameOverScreen;		// Keeps the image that loaded.
        GameOverScreen(std::string filename);
		~GameOverScreen();

        static const int LEVEL_WIDTH = 854;			// Size of width screen that will show the image level, in pixels.
        static const int LEVEL_HEIGHT = 480;		// Size of height screen that will show the image level, in pixels.
};
#endif