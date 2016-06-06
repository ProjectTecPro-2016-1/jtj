#ifndef BOX_H
#define BOX_H

#include "gameobject.hpp"
#include <string>

class Box : public GameObject {
    SDL_Surface *box;       // Pointer for box graphic elements.
    void drawSelf(SDL_Surface * surface);
    float speed;                            // Keep the actual speed of the box.
    static const int ACCELERATION = 1;      // Used for increments the box speed after the creation
                                            // of each box.
    static const int MAX_SPEED = 3;         // Keep the information about the maximum speed that the
                                            // box can achieve.

    public:
		bool lyingDown;                         // Contain information if the box is falling or not.
		static const int BOX_WIDTH = 38;        // All boxes pixel width.
		static const int BOX_HEIGHT = 38;       // All boxes pixel height.
        int x_position;                         // Keep the actual position of the box on axis X.
        int y_position;                         // Keep the actual position of the box on axis Y.
        bool used;                              // Contain information if the box is already in the
                                                // game or not.

        Box(std::string filename);
        ~Box();
        int getPositionX();
        int getPositionY();
        int getSpeed();
        void setPosition(int x, int y);
        void accelerate();
		void fall(vector<Box*>grid[12]);
};

#endif
