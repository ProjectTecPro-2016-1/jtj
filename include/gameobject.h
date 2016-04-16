#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <SDL/SDL.h>

using namespace std;

class GameObject {

    vector<GameObject*> children;   // Vector that stocks the objects of the game

    // -------------------------------------------------------------
	// Function: drawSelf()
	// Description: Draws the game object in a specific screen position according to the box attributes.
	// Parameters:
	//		SDL_Surface * surface;		Pointer for the surface where the graphic component will be drawn.
	// Return: void
	// Observation:
	// 		Function Without implementation.
	// -------------------------------------------------------------
    virtual void drawSelf(SDL_Surface * surface) = 0;
    public:
        virtual ~GameObject();
        void draw(SDL_Surface * surface);
        void addChild(GameObject * child);
};

#endif
