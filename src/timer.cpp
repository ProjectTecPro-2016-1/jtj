#include "timer.h"
#include <SDL/SDL.h>

Timer::Timer() {
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::waitDiff(float ratioFPS) {
    SDL_Delay (ratioFPS - get_ticks());
}


void Timer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

void Timer::stop() {
    started = false;
    paused = false;
}

void Timer::pause() {
    if ((started == true) && (paused == false)) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    } else {
        // Nothing to do
    }
}

void Timer::unpause() {
    if (paused == true) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    } else {
        // Nothing to do
    }
}

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

bool Timer::is_started() {
    return started;
}

bool Timer::is_paused() {
    return paused;
}
