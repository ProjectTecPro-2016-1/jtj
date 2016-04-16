#include "timer.h"
#include <SDL/SDL.h>

// -------------------------------------------------------------
// Function: Timer()
// Description: Builder of the Timer class which hosts the updates of class attributes.
// Return: void
// -------------------------------------------------------------
Timer::Timer() {
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

// -------------------------------------------------------------
// Function: waitDiff()
// Description: Function that generates a delay in the transition to a frame and another shipment.
// Parameters:
//		float ratioFPS;  		Time will the delay.
// Return: void
// -------------------------------------------------------------
void Timer::waitDiff(float ratioFPS) {
    SDL_Delay (ratioFPS - get_ticks());
}

// -------------------------------------------------------------
// Function: start()
// Description: Changes the game status attributes in order to start a new game.
// Return: void
// -------------------------------------------------------------
void Timer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

// -------------------------------------------------------------
// Function: stop()
// Description: Changes the game status attributes in order to paralyze.
// Return: void
// -------------------------------------------------------------
void Timer::stop() {
    started = false;
    paused = false;
}

// -------------------------------------------------------------
// Function: pause()
// Description: Changes the game status attributes in order to pause.
// Return: void
// -------------------------------------------------------------
void Timer::pause() {
    if ((started == true) && (paused == false)) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------
// Function: unpause()
// Description: Changes the game status attributes in order to take a break.
// Return: void
// -------------------------------------------------------------
void Timer::unpause() {
    if (paused == true) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------
// Function: get_ticks()
// Description: Returns the time of the current game.
// Return: int
// -------------------------------------------------------------
int Timer::get_ticks() {
    int valueForReturn = 0;

    if (started == true) {
        if (paused == true) {
            valueForReturn = pausedTicks;
        } else {
            valueForReturn = SDL_GetTicks() - startTicks;
        }
    } else {
        // Nothing to do
    }

    return valueForReturn;
}

// -------------------------------------------------------------
// Function: is_started()
// Description: Returns information on whether the game is started or not.
// Return: bool
// -------------------------------------------------------------
bool Timer::is_started() {
    return started;
}

// -------------------------------------------------------------
// Function: is_paused()
// Description: Returns information on whether the game is paused or not.
// Return: bool
// -------------------------------------------------------------
bool Timer::is_paused() {
    return paused;
}
