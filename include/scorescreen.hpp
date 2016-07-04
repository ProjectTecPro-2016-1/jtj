#ifndef SCORESCREEN_h
#define SCORESCREEN_h

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include <string>
#include "language.hpp"

class ScoreScreen {
	public:
		
		ScoreScreen(std::string filenameBackground, char const * filnameFont, Language * language);
		~ScoreScreen();
		
		int getLine();
		int getScorePoints();
		
		void popLine();
		void increaseScore(int value);
		void lines(int numero);
		void drawSelf(SDL_Surface *surface);
		void scoring(int value);
		
		SDL_Surface * getBoxMessage();
		SDL_Surface * getArmario();
		SDL_Surface * getScoreMessage();
		SDL_Color scoreTextColor;
		
		TTF_Font * getScoreFont();
		
		Language * language;

	private:
		TTF_Font *scoreFont; 	
		SDL_Surface *armario;	
		SDL_Surface *scoreMessage;	
		SDL_Surface *boxMessage;	
		
		int lineLeft; 
		int scorePoints;	
		
		void updateSelf();	// must be public for testing

		char scoreString[30];
		char lineString[30];

		static const int SCORE_WIDTH = 282;
		static const int SCORE_HEIGHT = 456;
		static const int SCORE_X_OFFSET = 506;
		static const int SCORE_Y_OFFSET = 10;
};
#endif