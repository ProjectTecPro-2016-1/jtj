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
	//		SDL_Surface *surface;		Pointer for the surface where the graphic component will be drawn.
	// Atributes: nothing
	// Return: void
	// -------------------------------------------------------------
    virtual void drawSelf(SDL_Surface *surface) = 0;
    public:

        // -------------------------------------------------------------
    	// Function: ~GameObject()
    	// Description: Virtual class destructor method
    	// Parameters: void
    	// Atributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        virtual ~GameObject();

        // -------------------------------------------------------------
    	// Function: draw()
    	// Description: Method that draws a object on the screen
    	// Parameters:
    	//		SDL_Surface *surface;		Pointer for the surface where the graphic component will be drawn.
    	// Atributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void draw(SDL_Surface *surface);

        // -------------------------------------------------------------
    	// Function: addChild()
    	// Description: Adds a element to the vector GamesObject*
    	// Parameters:
    	//		GameObject* child;		Pointer to the game object in question
    	// Atributes: nothing
    	// Return: void
    	// -------------------------------------------------------------
        void addChild(GameObject* child);
};


#endif
