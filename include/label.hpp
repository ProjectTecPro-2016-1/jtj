#ifndef LABEL_H
#define LABEL_H

#include "gameobject.hpp"
#include <string>

class Label : public GameObject {
	public:
		SDL_Surface * label;        // Pointer for label graphic elements.
		void drawSelf(SDL_Surface * surface);
		int xPosition;      // Where the label is localizated in axis X.
		int yPosition;      // Where the label is localizated in axis Y.
		
		static const int LABEL_WIDTH = 178;     // All label pixel width.
		static const int LABEL_HEIGHT = 100;    // All label pixel heigth.

		bool wasClicked(int xMouse, int yMouse);

		Label(std::string filename, int xPosition, int yPosition);
		~Label();
};

#endif
 
