#ifndef TIMER_H
#define TIMER_H

class Timer {
    public:

        Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        void waitDiff(float ratioFPS);

        int get_ticks();

        bool is_started();
        bool is_paused();

    private:
        int startTicks;			// Saves the time the game lasted or is lasting.
    	int pausedTicks;		// Saves the time the game lasted the rest of the game.

        bool paused;			// It contains information on whether the game is paused or not.
    	bool started;			// It contains information on whether the game is started or not.
};

#endif
