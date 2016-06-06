#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "sdlutil.hpp"
#include "level.hpp"
#include "timer.hpp"
#include "jack.hpp"
#include "label.hpp"
#include "initscreen.hpp"
#include "pausescreen.hpp"
#include "gameoverscreen.hpp"
#include "scorescreen.hpp"
#include "optionsscreen.hpp"

class Game {
    public:
        void init();
        void loop();
        void shutdown();

    private:
        void initGUI();
        void closeGUI();

        void wonGameScreen();
        void showOptionsScreen();

        void gameOvering();
        void gameOverScreenDraw();
        void gameOverScreenLoop();

        void pausingLevel();
        void pauseScreenDraw();
        void pauseScreenLoop();

        void initializingScreen();
        void initScreenDraw();
        void initScreenLoop();

        void loadCommonResources();
        void releaseCommonResources();

        void loadProfile();
        void saveProfile();

        void loadLevel();
        void releaseLevel();

        void updateTimeStep();
        void update();
        void draw();

        void runAI();
        void runPhysics();
        
        void recieveNetworkData();
        void sendNetworkData();
        
        void handleEventMouseButtonUp(SDL_Event & event);
        void handleEventMouseButtonDown(SDL_Event & event);
        void handleEventKeyDown(SDL_Event & event);
        void handleEventKeyUp(SDL_Event & event);
        void handleEventType(SDL_Event & event);
        void handleEvents();

        int checkIfSkip();

        bool checkColision(Jack * jack, std::vector<Box*> boxes);
        bool isGameFinished();
        bool isLevelFinished();

        SDL_Surface * screen;                  // Main Screen that will show graphic elements.
        SDL_Event event;                       // Keeps user action if exists.
        Jack * jack;                           // Pointer that keeps informationa bout Jack.
        Level * level;                         // Keep informations about actual level.
        Timer frameTime;                       // Controls loading and time of frames.
        ScoreScreen * score;                   // Centralizes informations about score on game.
        InitScreen * initScreen;               // Keep informations about Initial Screen.
        InitScreen * wonScreen;                // Controls the Won Game Screen which is executed 
                                               // at the end of each level.
        PauseScreen * pauseScreen;             // Controls the Pause Screen when user execute.
        GameOverScreen * gameOverScreen;       // Controls the Game Over Screen which is executed  
                                               // at the end of each level.
        OptionsScreen * optionsScreen;         // Controls Options Screen.
        Label * labelPlay;                     // Play Button on game.
        Label * labelOptions;                  // Options Button on game.
        Label * labelQuit;                     // Button that end game or cancels execution of 
                                               // some level.
        Label * labelMute;                     // Button from Options Screen that allows audio  
                                               // execution or not.
        Label * labelLoad;                     // Button from Options Screen that load a new game.
        Label * labelBack;                     // Button from Options Screen that returns to 
                                               // Initial Screen.
        float FRAME_MILISECOND;                // It contains the millisecond transition from one 
                                               // frame to another
        bool quitGame;                         // Information if the user wants to leave or not 
                                               // the game.
        bool quitLevel;                        // Information if necessary leave or not the level.
        bool pauseLevel;                       // Inforamtion if the game is paused or not.
        bool gameOver;                         // Information if the player lost or not the game.
        bool gameWon;                          // Information if the player won or not the game. 
        int linesDeleted;                      // Number of lines that have been completed by the 
                                               // player.
        int maxLevelLines;                     // Number of lines that is necessary to won the game.
        int actualLevel;                       // Contains the actual level number of player o game.

        static const int SCREEN_WIDTH = 854;   // Size width of the game screen.
        static const int SCREEN_HEIGHT = 480;  // Size game screen height.
        static const int SCREEN_BPP = 32;      // Number of bits per pixel permitted in the screen.
        static const int SCREEN_FPS = 60;      // Number of frames per second allowed.
};

#endif
