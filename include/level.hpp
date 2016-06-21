#ifndef LEVEL_H
#define LEVEL_H

#include "gameobject.hpp"
#include "box.hpp"
#include "enemy.hpp"
#include <string>
#include <vector>

class Level : public GameObject {
    void drawSelf(SDL_Surface * surface);
    //this stack shall handle the colision logic.
    public:
    SDL_Surface * level;        // Pointer for level graphic elements.
        vector<Enemy*> enemies;     // Vector that contains info about enemies.
		vector<Box*> boxes;         // Vector that contains info about boxes.
		vector<Box*> grid[12];      // Vector that contains the platform where the box falls.

        static const int LEVEL_WIDTH = 456;         // All level pixel width.
        static const int LEVEL_HEIGHT = 456;        // All level pixel height.
        static const int LEVEL_X_OFFSET = 50;       // Where the level is drawn on the specified surface in axis X.
        static const int LEVEL_Y_OFFSET = 10;       // Where the level is drawn on the specified surface in axis Y.

        Level(std::string filename);
        ~Level();

		vector<Box*> getBoxes();
};

#endif
