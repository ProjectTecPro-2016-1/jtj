#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <stdlib.h>
#include <sdlutil.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_ttf.h"
#include "level.h"
#include "timer.h"
#include "jack.h"
#include "label.h"
#include "initscreen.h"
#include "pausescreen.h"
#include "gameoverscreen.h"
#include "scorescreen.h"
#include "optionsscreen.h"

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

        SDL_Surface * screen;
        SDL_Event event;

        Jack * jack;
        Level * level;
        Timer frameTime;

        ScoreScreen * score;
        InitScreen * initScreen;
        InitScreen * wonScreen;
        PauseScreen * pauseScreen;
        GameOverScreen * gameOverScreen;
        OptionsScreen * optionsScreen;

        Label * labelPlay;
        Label * labelOptions;
        Label * labelQuit;
        Label * labelMute;
        Label * labelLoad;
        Label * labelBack;

        float FRAME_MILISECOND;

        bool quitGame;
        bool quitLevel;
        bool pauseLevel;
        bool gameOver;
        bool gameWon;

        int linesDeleted;
        int maxLevelLines;
        int actualLevel;

        static const int SCREEN_HEIGHT = 480;
        static const int SCREEN_WIDTH = 854;
        static const int SCREEN_BPP = 32;
        static const int SCREEN_FPS = 60;
};

#endif
