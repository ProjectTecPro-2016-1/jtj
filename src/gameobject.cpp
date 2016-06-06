#include "gameobject.hpp"

// -------------------------------------------------------------
// Function: ~GameObject()
// Description: Virtual class destructor method.
// Return: void
// -------------------------------------------------------------
GameObject::~GameObject() {
    int size = children.size();
    for (int i = 0; i < size; i++) {
        if (children[i]) {
            delete children[i];
        } else {
            // Nothing to do
        }
    }
}

// -------------------------------------------------------------
// Function: addChild()
// Description: Adds a element to the vector GamesObject*
// Parameters:
//		GameObject * child;		Pointer to the game object in question.
// Return: void
// -------------------------------------------------------------
void GameObject::addChild(GameObject * child) {
    children.push_back(child);
}

// -------------------------------------------------------------
// Function: draw()
// Description: Method that draws a object on the screen.
// Parameters:
//		SDL_Surface * surface;		Pointer for the surface where the graphic component will be drawn.
// Return: void
// -------------------------------------------------------------
void GameObject::draw(SDL_Surface * surface) {
    drawSelf(surface);
    int size = children.size();
    for (int i = size - 1; i >= 0; i--) {
        if (children[i]) {
            children[i]->draw(surface);
        } else {
            // Nothing to do
        }
    }
}
