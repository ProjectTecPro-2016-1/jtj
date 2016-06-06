#include "scorescreen.hpp"
#include "sdlutil.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

// -------------------------------------------------------------  
// Function: ScoreScreen()  
// Description: Constructor that loads image,socre font and score message for the Score Screen.
// Return: void  
// -------------------------------------------------------------  
ScoreScreen::ScoreScreen() {
    this->armario = SDLUtil::loadImage("resources/armario.png");
    this->scoreTextColor.r = 255;
    this->scoreTextColor.g = 255;
    this->scoreTextColor.b = 255;
    this->scoreFont = TTF_OpenFont ("resources/HanaleiRegular.ttf", 40);
    //assert(this->scoreFont != NULL && "It is not possible open ScoreFont");

	this->scorePoints = 0;
    sprintf(this->scoreString, "Score: %5d", this->scorePoints);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->scoreString, this->scoreTextColor);
    assert(this->scoreMessage != NULL && "It is not possible render scoreMessage scoreString in solid black");

    this->lineLeft = 99;
    sprintf(this->lineString, "Lines left: %d", this->lineLeft);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->lineString, this->scoreTextColor);
    assert(this->scoreMessage != NULL && "It is not possible render scoreMessage lineString in solid black");

}

// -------------------------------------------------------------  
// Function: ~ScoreScreen()  
// Description: Destructor of class that cleans the "armario" surface, score message and score font.
// Return: void  
// -------------------------------------------------------------  
ScoreScreen::~ScoreScreen() {
    TTF_CloseFont (scoreFont);
    SDL_FreeSurface (armario);
    SDL_FreeSurface (scoreMessage);
}

// -------------------------------------------------------------  
// Function: lines()  
// Description: Defines the number of rows that can be filled with boxes. 
// Parameters: 
//		int numero;		Number of lines that can be filled.
// Return: void  
// -------------------------------------------------------------  
void ScoreScreen::lines(int numero) {
    this->lineLeft = numero;
}

// -------------------------------------------------------------  
// Function: scoring()  
// Description: Writes the final value of the score on game.
// Parameters:
//		int value;		Value assigned the final score.	
// Return: void  
// -------------------------------------------------------------  
void ScoreScreen::scoring(int value) {
    this->scorePoints = value;
}

// -------------------------------------------------------------  
// Function: getLine()  
// Description: Keeps a value of filled lines to display on screen at the end of game.
// Return: int
// -------------------------------------------------------------  
int ScoreScreen::getLine() {
    return this->lineLeft;
}

// -------------------------------------------------------------  
// Function: getScorePoints()  
// Description: Keeps the value of player's score at the end of game.
// Return: int  
// -------------------------------------------------------------  
int ScoreScreen::getScorePoints() {
    return this->scorePoints;
}

// -------------------------------------------------------------  
// Function: popLine()  
// Description: Clean a line of boxes on screen when the player fills the line.
// Return: void  
// -------------------------------------------------------------  
void ScoreScreen::popLine() {
    this->lineLeft --;
    return ;
}

// -------------------------------------------------------------  
// Function: increaseScore()  
// Description: Records the player's score on game.
// Parameters:
//		int value;		Value added on score for the final score. 
// Return: void  
// -------------------------------------------------------------  
void ScoreScreen::increaseScore(int value) {
    this->scorePoints += value;
    return ;
}

// -------------------------------------------------------------  
// Function: updateSelf()  
// Description: Updates and shows on screen the score in the game and filled lines.
// Return: void  
// -------------------------------------------------------------  
void ScoreScreen::updateSelf() {
    sprintf(this->scoreString, "Score: %6d", this->scorePoints);
    this->scoreMessage = TTF_RenderText_Solid (this->scoreFont, this->scoreString, this->scoreTextColor);
    assert(this->scoreMessage != NULL && "It is not possible render scoreMessage scoreString in solid black");
    
    sprintf(this->lineString, "Line left: %2d", this->lineLeft);
    this->boxMessage = TTF_RenderText_Solid (this->scoreFont, this->lineString, this->scoreTextColor);
    assert(this->boxMessage != NULL && "It is not possible render boxMessage lineString in solid black");
    return ;
}

// -------------------------------------------------------------  
// Function: drawSelf()  
// Description: Applies score message, score font and "armario" image on screen to display the player's score. 
// Parameters:
//		SDL_Surface *surface;		Is the surface that the image will load.
// Return: void  
// -------------------------------------------------------------  
void ScoreScreen::drawSelf(SDL_Surface * surface) {
    updateSelf();
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET, ScoreScreen::SCORE_Y_OFFSET, this->armario, surface);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET + 20, ScoreScreen::SCORE_Y_OFFSET + 25, this->scoreMessage, surface);
    SDLUtil::applySurface (ScoreScreen::SCORE_X_OFFSET + 20, ScoreScreen::SCORE_Y_OFFSET + 75, this->boxMessage, surface);
}