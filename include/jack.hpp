#ifndef JACK_H
#define JACK_H

#include "gameobject.hpp"
#include "level.hpp"
#include <string>

class Jack : public GameObject {

    void drawSelf(SDL_Surface *surface);


    private:
        int x_position;                     // Variable that store Jack's position in X axis.
        int y_position;                     // Variable that store Jack's position in Y axis.
        bool dead;                          // Stores the information whether Jack is dead or not.
        int lastMove;                      // Stores Jack's last move. Used to stop Jack or make him walk again.
        int lastButOneMove;           // Stores Jack's last but one move. Used to stop Jack or make him walk again.
        int frame;                           // Variable for animation in drawSelf() method.
        int strength;                       // Stores Jack's strength to move boxes.
        int speed;                           // Stores Jack's actual horizontal speed.
        int verticalSpeed;               // Stores Jack's actual vertical Speed.
        bool jumping;                     // Stores the information wheter Jack is jumping or not.

    public:
        SDL_Rect spriteClips[9];
        SDL_Surface *jack;                                // Pointer for Jack's graphic elements.
        static const int ACCELERATION = 1;	// Used to increment the speed in the Y axis;
        static const int JACK_WIDTH = 38;	// Jack's horizontal size.
        static const int JACK_HEIGHT = 57;	// Jack's vertical size.

        Jack(std::string filename);
        ~Jack();

        bool isDead();

        void die();

        void setSpriteClips();
        void setSpriteClipsStopped();
        void setSpriteClipsOneRight();
        void setSpriteClipsSecondRight();
        void setSpriteClipsThirdRight();
        void setSpriteClipsJumpRight();
        void setSpriteClipsOneLeft();
        void setSpriteClipsSecondLeft();
        void setSpriteClipsThirdLeft();
        void setSpriteClipsJumpLeft();

        void move(int xBegin, int xRange, int yBegin, int yRange);
        void pushMove(int v);
        void popMove(int v);

        void jump(Level * level);
        int calculatesMaxJumpHeightLeft(Level * level);
        int calculatesMaxJumpHeightRight(Level * level);

        void controlsMaxJump1(int maxJumpHeightLeft, int maxJumpHeightRight);
        void controlsMaxJump2(int maxJumpHeightLeft, int maxJumpHeightRight);

        int getXPosition();
        void setXPosition(int x_position);

        int getYPosition();
        void setYPosition(int y_position);

        int getSpeed();
        void setSpeed(int speed);

        bool getDead();
        void setDead(bool dead);

        int getVerticalSpeed();
        void setVerticalSpeed(int verticalSpeed);

        bool getJumping();
        void setJumping(bool jumping);

        int getLastMove();
        void setLastMove(int lastMove);

        int getLastButOneMove();
        void setLastButOneMove(int lastButOneMove);

        int getStrength();
        void setStrength(int strength);

        int getFrame();
        void setFrame(int frame);

        void pushBox();

        int setLimit(int value, int limit1, int range);
};

#endif
