#ifndef SCORESCREEN_h
#define SCORESCREEN_h

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include <string>

class ScoreScreen {
	public:
		
		ScoreScreen();
		~ScoreScreen();
		void drawSelf(SDL_Surface *surface);
		int getLine();
		int getScorePoints();
		void popLine();
		void increaseScore(int value);
		void lines(int numero);
		void scoring(int value);
		TTF_Font *scoreFont; 	// public only for testing
		SDL_Surface *armario;	// public only for testing
		SDL_Surface *scoreMessage;	// public only for testing
		SDL_Color scoreTextColor;
		int scorePoints;	// public only for testing
		int lineLeft; // public only for testing
		void updateSelf();	// public only for testing
		SDL_Surface *boxMessage;	// public only for testing

	private:

		char scoreString[30];
		char lineString[30];

		static const int SCORE_WIDTH = 282;
		static const int SCORE_HEIGHT = 456;
		static const int SCORE_X_OFFSET = 506;
		static const int SCORE_Y_OFFSET = 10;
};
#endif