#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <cassert>
#include <cstdlib>
#include <stdio.h>
#include "SDL/SDL_ttf.h"
#include "sdlutil.h"
#include "game.h"
#include "enemy.h"
#include "box.h"
#include "scorescreen.h"

#define MAX_PLAYING_SOUNDS 10
// The higher this is, the louder each currently playing sound will be.
// However, high values may cause distortion if too many sounds are playing. 
// Experiment with this.
#define VOLUME_PER_SOUND SDL_MIX_MAXVOLUME / 2

using namespace std;

// Structure for loaded sounds.
typedef struct soundStruct {
    Uint8 * samples;        // Raw PCM sample data.
    Uint32 length;          // Size of sound data in bytes.
} soundT, * soundPointer;

// Structure for a currently playing sound.
typedef struct playingStruct {
    int active;                 // 1 if this sound should be played.
    soundPointer sound;         // Sound data to play.
    Uint32 position;            // Current position in the sound buffer.
} playingT, * playingPointer;

// Array for all active sound effects.
playingT playing[MAX_PLAYING_SOUNDS];

// Audio format specifications.
SDL_AudioSpec desired, obtained;

// Our loaded sounds and their formats.
soundT initScreenSound;
soundT level_1Sound;
soundT level_2Sound;
soundT level_3Sound;

void AudioCallback(void * userData, Uint8 * audio, int length) {
    // Avoid compiler warning.
    // userData += 0;
    userData = NULL;
    if (userData == NULL) {

    } else {

    }

    // Clear the audio buffer so we can mix samples into it.
    memset(audio, 0, length);

    // Mix in each sound.
    for (int i = 0; i < MAX_PLAYING_SOUNDS; i++) {
        if (playing[i].active) {
            Uint8 * soundBuffer;
            Uint32 soundLength;

            // Locate this sound's current buffer position.
            soundBuffer = playing[i].sound->samples;
            soundBuffer += playing[i].position;

            // Determine the number of samples to mix.
            if ((playing[i].position + length) > playing[i].sound->length) {
                soundLength = playing[i].sound->length - playing[i].position;
            } else {
                soundLength = length;
            }

            // Mix this sound into the stream.
            SDL_MixAudio(audio, soundBuffer, soundLength, VOLUME_PER_SOUND);

            // Update the sound buffer's position.
            playing[i].position += length;

            // Have we reached the end of the sound?
            if (playing[i].position >= playing[i].sound->length) {
                playing[i].active = 0;  // mark it inactive
            } else {
                // Nothing to do
            }
        } else {
            // Nothing to do
        }
    }
    return;
}

// This function loads a sound with SDL_LoadWAV and converts it to the specified sample format. 
// Returns 0 on success and 1 on failure. 
int LoadAndConvertSound(char * filename, SDL_AudioSpec * spec, soundPointer sound) {
    SDL_AudioCVT cvt;           // audio format conversion structure.
    SDL_AudioSpec loaded;       // format of the loaded data.
    Uint8 * newBuffer;

    // Load the WAV file in its original sample format.
    if (SDL_LoadWAV(filename, &loaded, &sound->samples, &sound->length) == NULL) {
        printf("Unable to load sound: %s\n", SDL_GetError());
        return 1;
    } else {
        // Nothing to do
    }

    // Build a conversion structure for converting the samples.
    // This structure contains the data SDL needs to quickly
    // convert between sample formats. 
    if (SDL_BuildAudioCVT(&cvt, loaded.format, 
                          loaded.channels, loaded.freq, 
                          spec->format, spec->channels, spec->freq) < 0) {
        printf("Unable to convert sound: %s\n", SDL_GetError());
        return 1;
    } else {
        // Nothing to do
    }

    // Since converting PCM samples can result in more data
    // (for instance, converting 8-bit mono to 16-bit stereo),
    // we need to allocate a new buffer for the converted data.
    // Fortunately SDL_BuildAudioCVT supplied the necessary information. 
    cvt.len = sound->length;
    newBuffer = (Uint8 *) malloc(cvt.len * cvt.len_mult);
    if (newBuffer == NULL) {
        printf("Memory allocation failed.\n");
        SDL_FreeWAV(sound->samples);
        return 1;
    } else {
        // Nothing to do
    }

    // Copy the sound samples into the new buffer.
    memcpy(newBuffer, sound->samples, sound->length);

    // Perform the conversion on the new buffer.
    cvt.buf = newBuffer;
    if (SDL_ConvertAudio(&cvt) < 0) {
        printf("Audio conversion error: %s\n", SDL_GetError());
        free(newBuffer);
        SDL_FreeWAV(sound->samples);
        return 1;
    } else {
        // Nothing to do
    }

    // Swap the converted data for the original.
    SDL_FreeWAV(sound->samples);
    sound->samples = newBuffer;
    sound->length = sound->length * cvt.len_mult;

    // Success!
    printf("'%s' was loaded and converted successfully.\n", filename);
    return 0;
}


// Removes all currently playing sounds.
void ClearPlayingSounds(void) {
    for (int i = 0; i < MAX_PLAYING_SOUNDS; i++) {
        playing[i].active = 0;
    }
}

// Adds a sound to the list of currently playing sounds.
// AudioCallback will start mixing this sound into the stream
// the next time it is called (probably in a fraction of a second). 
int PlaySound(soundPointer sound) {
    int i;
    // Find an empty slot for this sound.
    for (i = 0; i < MAX_PLAYING_SOUNDS; i++) {
        if (playing[i].active == 0) {
            break;
        } else {
            // Nothing to do
        }
    }

    // Report failure if there were no free slots.
    if (i == MAX_PLAYING_SOUNDS) {
        return 1;
    } else {
        // Nothing to do
    }

    // The 'playing' structures are accessed by the audio callback,
    // so we should obtain a lock before we access them. 
    SDL_LockAudio();
    playing[i].active = 1;
    playing[i].sound = sound;
    playing[i].position = 0;
    SDL_UnlockAudio();

    return 0;
}

void Game::init() {
    initGUI();
    loadCommonResources();

    FRAME_MILISECOND = 1000 / SCREEN_FPS;
    this->quitGame = false;
    this->quitLevel = false;
    this->pauseLevel = false;
    this->gameOver = false;
    this->actualLevel = 1;
    this->linesDeleted = 0;

    int result_SDL_FillRect = 0;
    result_SDL_FillRect = SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    assert(result_SDL_FillRect >= 0 && "Problem to show a rect of main screen.");

    if (true) {

    } else {

    }

    return;
}

void Game::loop() {
    while (isGameFinished() == false) {
        initializingScreen();

        if (isGameFinished()) {
            break;
        } else {
            // Nothing to do
        }
        loadLevel();

        while (isLevelFinished() == false) {
            updateTimeStep();
            recieveNetworkData();
            handleEvents();
            runAI();
            runPhysics();
            update();
            sendNetworkData();
            draw();
        }
        wonGameScreen();
        releaseLevel();
    }
    return;
}

void Game::shutdown() {
    SDL_LockAudio();
    free(initScreenSound.samples);
    free(level_1Sound.samples);
    free(level_2Sound.samples);
    free(level_3Sound.samples);
    SDL_UnlockAudio();

    closeGUI();
    return;
}

void Game::initGUI() {
    int result_SDL_Init = 0;
    result_SDL_Init = SDL_Init(SDL_INIT_EVERYTHING);
    assert(result_SDL_Init >= 0 && "Problem to init SDL. Impossible play the game.");

    int result_TTF_Init = 0;
    result_TTF_Init = TTF_Init();
    assert(result_TTF_Init >= 0 && "Problem to init TTF. Can't show the font of the game.");

    SDL_WM_SetCaption("Jack, The Janitor", NULL);
    SDL_WM_SetIcon(IMG_Load("resources/Logo_WareHouse_64x64.png"), NULL);

    this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
    assert(this->screen != NULL && "Problem to set a video mode. Can't show the screen of the game.");
        
    return;
}

void Game::closeGUI() {
    SDL_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return;
}

void Game::wonGameScreen() {
    if (this->gameWon == true) {

        this->actualLevel++;

        cout << "Level: " << actualLevel << endl;

        wonScreen = new InitScreen("resources/backgroundwonscreen.png");

        bool playButton = false;
        bool quitButton = false;

        this->quitGame = false;
        this->quitLevel = false;
        this->pauseLevel = false;
        this->gameOver = false;

        SDL_Delay(5);

        while (SDL_WaitEvent(&event) != 0 && playButton == false && quitButton == false) {
            switch (event.type) {
                case SDL_QUIT:
                    quitButton = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        playButton = true;
                    } else {
                        // Nothing to do
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_p:
                        case SDLK_w:
                        case SDLK_a:
                        case SDLK_s:
                        case SDLK_d:
                            playButton = true;
                            break;

                        case SDLK_q:
                        case SDLK_ESCAPE:
                            quitButton = true;
                            break;

                        default:
                            // Nothing to do
                            break;
                    }
                    break;

                default:
                    // Nothing to do
                    break;
            }
            wonScreen->draw(this->screen);

            int result_SDL_Flip = 0;
            result_SDL_Flip = SDL_Flip(this->screen);
            assert(result_SDL_Flip >= 0 && "Fail to call SDL_Flip for game won screen, and impossible to continue the game.");

            if (quitButton) {
                this->quitLevel = true;
                this->quitGame = true;
            } else {
                // Nothing to do
            }
        }
        
        int result_SDL_FillRect = 0;
        result_SDL_FillRect = SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        assert(result_SDL_FillRect >= 0 && "Problem to show a rect of game won screen.");

        delete wonScreen;
    } else {
        return;
    }

    return;
}

void Game::showOptionsScreen() {

    optionsScreen = new OptionsScreen("resources/backgroundoptionsscreen.png");

    labelMute = new Label("resources/mutebutton.png", 483, 68);
    optionsScreen->addChild(labelMute);

    labelLoad = new Label("resources/loadbutton.png", 483, 191);
    optionsScreen->addChild(labelLoad);

    labelBack = new Label("resources/backbutton.png", 483, 314);
    optionsScreen->addChild(labelBack);

    bool muteButton = false;
    bool loadButton = false;
    bool backButton = false;

    while (SDL_WaitEvent(&event) != 0 && backButton == false) {
        switch (event.type) {
            case SDL_QUIT:
                backButton = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    muteButton = labelMute->wasClicked(event.button.x, event.button.y);
                    loadButton = labelLoad->wasClicked(event.button.x, event.button.y);
                    backButton = labelQuit->wasClicked(event.button.x, event.button.y);
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                    case SDLK_ESCAPE:
                        backButton = true;
                        break;

                    default:
                        // Nothing to do
                        break;
                    }
                break;

            default:
                // Nothing to do
                break;
        }
        optionsScreen->draw(this->screen);

        int result_SDL_Flip = 0;
        result_SDL_Flip = SDL_Flip(this->screen);
        assert(result_SDL_Flip >= 0 && "Fail to call SDL_Flip for option screen, and impossible to continue the game.");

        if (muteButton == true) {
            if (SDL_GetAudioStatus() == SDL_AUDIO_PLAYING) {
                SDL_PauseAudio(1);
            } else {
                SDL_PauseAudio(0);
            }
            muteButton = false;
        } else {
            // Nothing to do
        }

        if (loadButton == true) {
            cout << "Não implementado, cara... Se deu mal =P" << endl;
        } else {
            // Nothing to do
        }
    }

    int result_SDL_FillRect = 0;
    result_SDL_FillRect = SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    assert(result_SDL_FillRect >= 0 && "Problem to show a rect of option screen.");

    delete optionsScreen;

    return;
}

void Game::gameOvering() {
    gameOverScreenDraw();
    jack->popMove(3);
    jack->popMove(-3);
    gameOverScreenLoop();

    return;
}

void Game::gameOverScreenDraw() {
    gameOverScreen = new GameOverScreen("resources/backgroundgameover.png");

    labelPlay = new Label("resources/startbutton.png", 483, 68);
    gameOverScreen->addChild(labelPlay);

    labelOptions = new Label("resources/optionsbutton.png", 483, 191);
    gameOverScreen->addChild(labelOptions);

    labelQuit = new Label("resources/exitbutton.png", 483, 314);
    gameOverScreen->addChild(labelQuit);

    return;
}

void Game::gameOverScreenLoop() {
    bool playButton = false;
    bool quitButton = false;
    bool optionsButton = false;

    this->quitGame = false;
    this->quitLevel = true;

    do {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    this->quitLevel = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (labelPlay->wasClicked(event.button.x, event.button.y)) {
                            playButton = true;
                            this->quitGame = false;
                        } else if (labelOptions->wasClicked(event.button.x, event.button.y)) {
                            optionsButton = true;
                        } else if (labelQuit->wasClicked(event.button.x, event.button.y)) {
                            this->quitGame = true;
                            quitButton = true;
                        } else {
                            // Nothing to do
                        }
                    } else {
                        // Nothing to do
                    }
                    break;

                default:
                    // Nothing to do
                    break;
            }
        }

        gameOverScreen->draw(this->screen);

        int result_SDL_Flip = 0;
        result_SDL_Flip = SDL_Flip(this->screen);
        assert(result_SDL_Flip >= 0 && "Fail to call SDL_Flip for gameover screen, and impossible to continue the game.");

    } while (playButton == false && optionsButton == false && quitButton == false);

    
    int result_SDL_FillRect = 0;
    result_SDL_FillRect = SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    assert(result_SDL_FillRect >= 0 && "Problem to show a rect of option screen.");

    return;
}

void Game::pausingLevel() {
    pauseScreenDraw();
    jack->popMove(3);
    jack->popMove(-3);
    pauseScreenLoop();

    return;
}

void Game::pauseScreenDraw() {
    pauseScreen = new PauseScreen("resources/backgroundpausescreen.png");

    labelPlay = new Label("resources/startbutton.png", 483, 68);
    pauseScreen->addChild(labelPlay);

    labelOptions = new Label("resources/optionsbutton.png", 483, 191);
    pauseScreen->addChild(labelOptions);

    labelQuit = new Label("resources/exitbutton.png", 483, 314);
    pauseScreen->addChild(labelQuit);

    return;
}

void Game::pauseScreenLoop() {
    bool playButton = false;
    bool quitButton = false;
    bool optionsButton = false;

    this->quitLevel = false;

    while (SDL_WaitEvent(&event) != 0 && playButton == false && quitButton == false) {
        switch (event.type) {
            case SDL_QUIT:
                quitButton = true;
                this->quitLevel = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    playButton = labelPlay->wasClicked(event.button.x, event.button.y);
                    optionsButton = labelOptions->wasClicked(event.button.x, event.button.y);
                    quitButton = labelQuit->wasClicked(event.button.x, event.button.y);
                } else {
                    // Nothing to do
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_p:
                        this->pauseLevel = false;
                        playButton = true;
                        break;

                    case SDLK_q:
                    case SDLK_ESCAPE:
                        this->quitLevel = true;
                        quitButton = true;
                        break;

                    default:
                        // Nothing to do
                        break;
                }
                break;

            default:
                // Nothing to do
                break;
        }
        pauseScreen->draw(this->screen);

        int result_SDL_Flip = 0;
        result_SDL_Flip = SDL_Flip(this->screen);
        assert(result_SDL_Flip >= 0 && "Fail to call SDL_Flip for pause screen, and impossible to continue the game.");

        if (playButton == true) {
            this->pauseLevel = false;
        } else {
            // Nothing to do
        }

        if (quitButton == true) {
            this->quitLevel = true;
        } else {
            // Nothing to do
        }

        if (optionsButton) {
            showOptionsScreen();
            optionsButton = false;
        } else {
            // Nothing to do
        }
    }

    int result_SDL_FillRect = 0;
    result_SDL_FillRect = SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    assert(result_SDL_FillRect >= 0 && "Problem to show a rect of pause screen.");

    delete pauseScreen;

    return;
}

void Game::initializingScreen() {
    // Clear the list of playing sounds.
    ClearPlayingSounds();

    // SDL's audio is initially paused. Start it.
    SDL_PauseAudio(0);

    PlaySound(&initScreenSound);
    
    initScreenDraw();
    initScreenLoop();

    SDL_PauseAudio(1);

    return;
}

void Game::initScreenDraw() {
    initScreen = new InitScreen("resources/backgroundinitscreen.png");

    labelPlay = new Label("resources/startbutton.png", 483, 68);
    initScreen->addChild(labelPlay);

    labelOptions = new Label("resources/optionsbutton.png", 483, 191);
    initScreen->addChild(labelOptions);

    labelQuit = new Label("resources/exitbutton.png", 483, 314);
    initScreen->addChild(labelQuit);

    return;
}

void Game::initScreenLoop() {
    bool playButton = false;
    bool quitButton = false;
    bool optionsButton = false;

    this->quitGame = false;
    this->quitLevel = false;
    this->pauseLevel = false;
    this->gameOver = false;

    while (SDL_WaitEvent(&event) != 0 && playButton == false && quitButton == false) {
        switch (event.type) {
            case SDL_QUIT:
                quitButton = true;
                this->quitLevel = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    playButton = labelPlay->wasClicked(event.button.x, event.button.y);
                    optionsButton = labelOptions->wasClicked(event.button.x, event.button.y);
                    quitButton = labelQuit->wasClicked(event.button.x, event.button.y);
                } else {
                    // Nothing to do
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_p:
                        playButton = true;
                        break;

                    case SDLK_q:
                    case SDLK_ESCAPE:
                        this->quitLevel = true;
                        quitButton = true;
                        break;

                    default:
                        // Nothing to do
                        break;
                }
                break;

            default:
                // Nothing to do
                break;
        }
        initScreen->draw(this->screen);

        int result_SDL_Flip = 0;
        result_SDL_Flip = SDL_Flip(this->screen);
        assert(result_SDL_Flip >= 0 && "Fail to call SDL_Flip for initial screen, and impossible to continue the game.");

        if (quitButton) {
            this->quitLevel = true;
            this->quitGame = true;
        } else {
            // Nothing to do
        }

        if (optionsButton) {
            showOptionsScreen();
            optionsButton = false;
        } else {
            // Nothing to do
        }
    }

    int result_SDL_FillRect = 0;
    result_SDL_FillRect = SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    assert(result_SDL_FillRect >= 0 && "Problem to show a rect of init screen.");

    delete initScreen;

    return;
}

void Game::loadCommonResources() {
    score = new ScoreScreen();

    // Open the audio device. The sound driver will try to give us
    // the requested format, but it might not succeed. The 'obtained'
    // structure will be filled in with the actual format data. 
    desired.freq = 44100;               // desired output sample rate
    desired.format = AUDIO_S16;         // request signed 16-bit samples
    desired.samples = 4096;             // this is more or less discretionary
    desired.channels = 2;               // ask for stereo
    desired.callback = AudioCallback;
    desired.userdata = NULL;            // we don't need this

    int result_SDL_OpenAudio = SDL_OpenAudio(&desired, &obtained);
    if (result_SDL_OpenAudio >= 0) {
        // Load our sound files and convert them to the sound card's format.
        char initScreenSoundName[26] = "resources/init_screen.wav";
        char level_1SoundName[26] = "resources/level_1.wav";
        char level_2SoundName[26] = "resources/level_2.wav";
        char level_3SoundName[26] = "resources/level_3.wav";
        
        int result_LoadAndConverSoundInitScreen = 0;
        int result_LoadAndConverSoundLevel1 = 0;
        int result_LoadAndConverSoundLevel2 = 0;
        int result_LoadAndConverSoundLevel3 = 0;
        result_LoadAndConverSoundInitScreen = LoadAndConvertSound(initScreenSoundName, &obtained, 
                                                                  &initScreenSound);
        result_LoadAndConverSoundLevel1 = LoadAndConvertSound(level_1SoundName, &obtained, 
                                                              &level_1Sound);
        result_LoadAndConverSoundLevel2 = LoadAndConvertSound(level_2SoundName, &obtained, 
                                                              &level_2Sound);
        result_LoadAndConverSoundLevel3 = LoadAndConvertSound(level_3SoundName, &obtained, 
                                                              &level_3Sound);

        bool validateLoadAndConvertSound = true;
        validateLoadAndConvertSound = result_LoadAndConverSoundInitScreen == 0 &&
                                      result_LoadAndConverSoundLevel1 == 0 &&
                                      result_LoadAndConverSoundLevel2 == 0 &&
                                      result_LoadAndConverSoundLevel3 == 0;

        if (validateLoadAndConvertSound == false){
            cout << "Unable to load sound." << endl;
            return;
        } else {
            // Nothing to do
        }
    } else {
        cout << "Unable to open audio device: " << SDL_GetError() << endl;
        return;
    }

    return;
}

void Game::releaseCommonResources() {
    return;
}

void Game::loadProfile() {
    return;
}

void Game::saveProfile() {
    return;
}

void Game::loadLevel() {

    ClearPlayingSounds();
    string level_1_file = "resources/level_1.png";
    string level_2_file = "resources/level_2.png";
    string level_3_file = "resources/level_3.png";
    string level_1_spec = "resources/level_1";
    string level_2_spec = "resources/level_2";
    string level_3_spec = "resources/level_3";
    string currentLevelFile;
    string currentLevelSpec;
    if (this->actualLevel > 3) {
        this->actualLevel = 1;
    } else {
        // Nothing to do
    }

    switch (this->actualLevel) {
        case 1:
            currentLevelFile = level_1_file;
            currentLevelSpec = level_1_spec;
            PlaySound(&level_1Sound);
            SDL_PauseAudio(0);
            break;
        case 2:
            currentLevelFile = level_2_file;
            currentLevelSpec = level_2_spec;
            PlaySound(&level_2Sound);
            SDL_PauseAudio(0);
            break;
        case 3:
            currentLevelFile = level_3_file;
            currentLevelSpec = level_3_spec;
            PlaySound(&level_3Sound);
            SDL_PauseAudio(0);
            break;
        default:
            cout << "could not load level file" << endl;
            return;
    }

    ifstream levelFile;
    string numberOfLevel = "";
    string numberOfBoxes = "";
    string numberOfEnemies = "";
    string maxLines = "";

    level = new Level(currentLevelFile);
    levelFile.open(currentLevelSpec.c_str());
    getline(levelFile, numberOfLevel);
    getline(levelFile, numberOfBoxes);
    getline(levelFile, numberOfEnemies);
    getline(levelFile, maxLines);
    levelFile.close();

    assert(numberOfLevel != "" && 
          "Impossible to read the number of level, can't continue the game.");
    assert(numberOfBoxes != "" && 
          "Impossible to read the number of box in level, can't continue the game.");
    assert(numberOfEnemies != "" && 
          "Impossible to read the number of enemies in the level, can't continue the game.");
    assert(maxLines != "" && 
          "Impossible to read the number of lines to completo the level, can't continue the game.");

    int nrBoxes = atoi(numberOfBoxes.c_str());

    for (int i = 0; i < nrBoxes; i++) {
        Box * box = new Box("resources/box.png");
        level->boxes.push_back(box);
        level->addChild(box);
    }

    int nrEnemies = atoi(numberOfEnemies.c_str());

    for (int i = 0; i < nrEnemies; i++) {
        Enemy * enemy = new Enemy("resources/enemy_sprites.png");
        enemy->setSpriteClips();
        level->enemies.push_back(enemy);
        level->addChild(enemy);
    }

    this->maxLevelLines = atoi(maxLines.c_str());
    score->lines(this->maxLevelLines);
    score->scoring(0);
    this->linesDeleted = 0;
    this->gameWon = false;

    jack = new Jack("resources/jack_sprites.png");
    jack->setSpriteClips();
    level->addChild(jack);

    cout << "Level\t" << this->actualLevel << endl;
    cout << "Number of Boxes: " << nrBoxes << endl;
    cout << "Number of Enemies: " << nrEnemies << endl;
    cout << "Max Leve Lines: " << maxLevelLines << endl;

    return;
}

void Game::releaseLevel() {
    if (level) {
        delete level;
    } else {
        // Nothing to do
    }
    return;
}

void Game::updateTimeStep() {
    frameTime.start();
    return;
}

void Game::update() {
    if (linesDeleted >= maxLevelLines) {
        this->gameWon = true;
    } else {
        // Nothing to do
    }

    if (jack->isDead()) {
        gameOvering();
    } else {
        // Nothing to do
    }

    if (score->getLine() < 0) {
        gameOver = true;
    } else {
        // Nothing to do
    }

    if (score->getScorePoints() > 99999) {
        gameOver = true;
    } else {
        // Nothing to do
    }

    if (pauseLevel == true) {
        pausingLevel();
    } else {
        // Nothing to do
    }

    if (isGameFinished()) {
        gameOvering();
    } else {
        // Nothing to do
    }

    if (this->gameWon == true) {
        this->quitLevel = true;
    } else {
        // Nothing to do
    }

    return;
}

void Game::draw() {
    if (checkIfSkip() == 0) {

        int result_SDL_FillRect = 0;
        result_SDL_FillRect = SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        assert(result_SDL_FillRect >= 0 && "Problem to show a rect of screen.");

        level->draw(this->screen);
        score->drawSelf(this->screen);
        
        int result_SDL_Flip = 0;
        result_SDL_Flip = SDL_Flip(this->screen);
        assert(result_SDL_Flip >= 0 && "Problem to call the SDL_Flip function. Finally the game.");
    } else {
        // Nothing to do
    }

    return;
}

void Game::runAI() {
    for (unsigned int i = 0; i < level->enemies.size(); i++) {
        level->enemies[i]->throwBox(level->boxes);
        level->enemies[i]->move();
    }
    return;
}

void Game::runPhysics() {

    // cout << "Checando colisão" << endl;
    bool checkColisionExist = false;
    checkColisionExist = checkColision(jack, level->boxes);
    if (checkColisionExist == true) {
        jack->die();
    } else {
        // Nothing to do
    }
    // cout << "Colisão checada." << endl;

    // cout << "Jogador (" << jack->getXPosition() << "," << jack->getYPosition() << ")" << endl;
    // Notice that when the game restarts, another box is pushed into the array
    // cout << "Derrubando caixas" << endl;
    for (unsigned int i = 0; i < level->boxes.size(); i++) {
        if (level->boxes[i]->used == true) {
            level->boxes[i]->fall(level->grid);
        } else {
            // Nothing to do
        }
    }

    int xInitialLevel = Level::LEVEL_X_OFFSET;
    int xRangeLevel = Level::LEVEL_WIDTH + Level::LEVEL_X_OFFSET;

    // int yinit=Level::LEVEL_Y_OFFSET;
    // int yfinal=Level::LEVEL_HEIGHT-Level::LEVEL_Y_OFFSET;
    
    int jackPositionX = (jack->getXPosition() - Level::LEVEL_X_OFFSET) / Jack::JACK_WIDTH;
    int jackPositionY = (jack->getYPosition() - Level::LEVEL_Y_OFFSET + Jack::JACK_HEIGHT + 19) / 38;

    // Looking for the first box before Jack
    // cout << "Procurando pela caixa móvel antes do Jack" << endl;
    int boxMobileBeforeJack = -1;
    for (int i = jackPositionX; i >= 0; i--) {
        if ((level->grid[i].size() + jackPositionY) >= 12) {
            xInitialLevel = Level::LEVEL_X_OFFSET + (i + 1) * Box::BOX_WIDTH;
            if ((level->grid[i].size() + jackPositionY) == 12) {
                if (i > 0) {
                    if (level->grid[i-1].size() >= level->grid[i].size()) {
                        break;
                    } else {
                        boxMobileBeforeJack = i;
                    }
                } else {
                    // Nothing to do
                }
            } else {
                // Nothing to do
            }
            break;
        } else {
            // Nothing to do
        }
    }

    // cout << "Procurando pela caixa móvel depois do Jack" << endl;
    // Looking for the first box after Jack
    int boxMobileAfterJack = -1;
    for (int i = jackPositionX; i < 12; i++) {
        if ((level->grid[i].size() + jackPositionY) >= 12) {
            xRangeLevel = Level::LEVEL_X_OFFSET + (i) * 38 - xInitialLevel;
            if ((level->grid[i].size() + jackPositionY) == 12) {
                if (i<11){
                    if (level->grid[i+1].size() >= level->grid[i].size()) {
                       break;
                    } else {
                        boxMobileAfterJack = i;
                    }
                } else {
                    // Nothing to do
                }
            } else {
                // Nothing to do
            }
            break;
        } else {
            // Nothing to do
        }
    }

    for (int i = 0; i < 12; ++i) {
        // cout << i << " " << level->grid[i] << endl;
        if (level->grid[i].size() > 7) {
            this->quitGame = true;
        } else {
            // Nothing to do
        }
    }


    int quantidadeDeCaixas = 0;
    for (int i = 0; i < 12; ++i) {
        if (level->grid[i].size() > 0) {
            quantidadeDeCaixas++;
        } else {
            // Nothing to do
        }
    }

    if (quantidadeDeCaixas == 12) {
        score->increaseScore(1000);
        score->popLine();
        linesDeleted++;
        if (jack->jumping != true) {
            jack->verticalSpeed = -10;
            jack->jumping = true;
        } else {
            // Nothing to do
        }
        for (int i = 0; i < 12; ++i) {
            Box * boxToDelete = level->grid[i].back();
            for (vector<Box*>::iterator it = level->boxes.begin(); it != level->boxes.end(); it++) {
                if (*it == boxToDelete) {
                    // delete level->boxes.it;
                    Box * myBox = *it;
                    level->boxes.erase(it);
                    myBox->used = false;
                    break;
                } else {
                    // Nothing to do
                }
            }
            level->grid[i].pop_back();
        }
    } else {
        // Nothing to do
    }

    if (xInitialLevel < Level::LEVEL_X_OFFSET) {
        xInitialLevel = Level::LEVEL_X_OFFSET;
    } else {
        // Nothing to do
    }

    if (xRangeLevel + xInitialLevel > (Level::LEVEL_WIDTH + Level::LEVEL_X_OFFSET)) {
        xRangeLevel = (Level::LEVEL_WIDTH + Level::LEVEL_X_OFFSET) - xInitialLevel;
    } else {
        // Nothing to do
    }

    if (boxMobileBeforeJack != -1) {
        // cout << "Primeira caixa móvel antes de jack: " << boxMobileBeforeJack << endl;
        if (jack->getXPosition() == (((boxMobileBeforeJack + 1) * Box::BOX_WIDTH) + Level::LEVEL_X_OFFSET)) {
            // cout << "Colidiu com uma caixa a esquerda!!! forca: " << jack->strength << endl;
            if (jack->strength < 10){
                jack->strength++;
            } else {
                // Nothing to do
            }

            if ((jack->strength >= 10) && (jack->speed < 0)) {
                Box * boxTransition = level->grid[boxMobileBeforeJack].back();
                boxTransition->x_position -= Box::BOX_WIDTH;
                level->grid[boxMobileBeforeJack].pop_back();
                boxTransition->lyingDown = false;
                boxTransition->fall(level->grid);
            } else {
                // Nothing to do
            }
            // level->grid[boxMobileBeforeJack-1].push_back(boxTransition);
        } else {
            // Nothing to do
        }
    } else {
        // Nothing to do
    }

    if (boxMobileAfterJack != -1) {
        // cout << "Primeira caixa móvel depois de jack: " << boxMobileAfterJack << endl;
        if ((jack->getXPosition() + Jack::JACK_WIDTH) == (xRangeLevel + xInitialLevel)) {
            // cout << "Colidiu com uma caixa a direta!!!" << endl;
            if (jack->strength < 10){
                jack->strength++;
            } else {
                // Nothing to do
            }
            if ((jack->strength >= 10) && (jack->speed > 0)) {
                Box * boxTransitionRight = level->grid[boxMobileAfterJack].back();
                boxTransitionRight->x_position += Box::BOX_WIDTH;
                level->grid[boxMobileAfterJack].pop_back();
                boxTransitionRight->lyingDown = false;
                boxTransitionRight->fall(level->grid);
            } else {
                // Nothing to do
            }
        } else {
            // Nothing to do
        }
    } else {
        // Nothing to do
    }

    if (jack->speed == 0){
            jack->strength = 0;
    } else {
        // Nothing to do
    }
    // cout << "Limite a direita do jack: " << xRangeLevel+xInitialLevel << endl;
    // cout << "Limite a esquerda do jack: " << xInitialLevel << endl;
    jack->move(xInitialLevel, xRangeLevel, Level::LEVEL_Y_OFFSET, Level::LEVEL_HEIGHT);

    // cout << "Jack moveu" << endl;
    jack->jump(level);
    return;
}

void Game::recieveNetworkData() {
    return;
}

void Game::sendNetworkData() {
    return;
}

void Game::handleEventMouseButtonUp(SDL_Event & event) {
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            // printf("Posicao onde o botao foi liberado: (%d, %d)\n", event.button.x, event.button.y);
            break;
        default:
            // Nothing to do
            break;
    }

    return;
}


void Game::handleEventMouseButtonDown(SDL_Event & event) {
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            // Nothing to do
            break;
        case SDL_BUTTON_RIGHT:
            // Nothing to do
            break;
        default:
            // Nothing to do
            break;
    }

    return;
}

void Game::handleEventKeyDown(SDL_Event & event) {
    switch (event.key.keysym.sym) {
        case (SDLK_ESCAPE):
            this->quitLevel = true;
            break;

        case (SDLK_w):
        case (SDLK_UP):
        case (SDLK_SPACE):
            if(jack->jumping == true) {
                break;
            } else {
                // Nothing to do
            }
            jack->verticalSpeed = -10;
            jack->jumping = true;
            break;

        case (SDLK_a):
        case (SDLK_LEFT):
            jack->pushMove(-3);
            break;

        case (SDLK_s):
            break;

        case (SDLK_q):
            this->gameOver = true;
            this->quitLevel = true;
            break;

        case (SDLK_d):
        case (SDLK_RIGHT):
            jack->pushMove(3);
            break;

        case (SDLK_p):
            if (this->pauseLevel == true) {
                this->pauseLevel = false;
            }
            else {
                this->pauseLevel = true;
            }
            break;

        default:
            cout << event.key.keysym.sym << endl;
            break;
    }
}

void Game::handleEventKeyUp(SDL_Event & event) {
    switch (event.key.keysym.sym) {
        case (SDLK_a):
        case (276):
            jack->popMove(-3);
            break;

        case (SDLK_d):
        case (275):
            jack->popMove(3);
            break;

        default:
            // Nothing to do
            break;
    }
}

void Game::handleEventType(SDL_Event & event) {
    switch (event.type) {
        case SDL_QUIT:
            this->quitLevel = true;
            break;

        case SDL_KEYDOWN:
            handleEventKeyDown(event);
            break;

        case SDL_KEYUP:
            handleEventKeyUp(event);
            break;

        case SDL_MOUSEBUTTONDOWN:
            handleEventMouseButtonDown(event);
            break;

        case SDL_MOUSEBUTTONUP:
            handleEventMouseButtonUp(event);
            break;

        default:
            // Nothing to do
            break;
    }
}

void Game::handleEvents() {
    while (SDL_PollEvent (&event)) {
        handleEventType(event);
    }
    return;
}

int Game::checkIfSkip() {
    if (frameTime.get_ticks() < FRAME_MILISECOND) {
        frameTime.waitDiff(FRAME_MILISECOND);
        return 0;
    }
    else {
        return 1;
    }
}

bool Game::checkColision (Jack * jack, std::vector<Box*> boxes) {

    for (unsigned int i = 0; i < boxes.size(); ++i) {
        // cout << "Box " << i << "(" << boxes[i]->getPositionX() << "," << boxes[i]->getPositionY() << ")\t";
        // cout << "(" << boxes[i]->getPositionX() + 38 << "," << boxes[i]->getPositionY() + 38 << ")" << endl;

        int jackRight = jack->getXPosition() + Box::BOX_WIDTH;
        int jackLeft = jack->getXPosition();
        int jackTop = jack->getYPosition();
        int jackBottom = jack->getYPosition() + Jack::JACK_HEIGHT;
        int boxRight = boxes[i]->getPositionX() + Box::BOX_HEIGHT;
        int boxLeft = boxes[i]->getPositionX();
        int boxTop = boxes[i]->getPositionY();
        int boxBottom = boxes[i]->getPositionY() + Box::BOX_HEIGHT;

        if ((jackRight == boxRight && jackLeft == boxLeft) && ((jackTop <= boxBottom) && (boxBottom < jackBottom))) {
            return true;
        } else {
            // Nothing to do
        }

        if (((boxLeft < jackLeft && jackLeft < boxRight) && (boxTop < jackTop && jackTop < boxBottom)) ||
            ((jackLeft < boxLeft && boxLeft < jackRight) && (jackTop < boxTop && boxTop < jackBottom))) {

            // cout << "Jack: ("<< jackLeft <<", " << jackRight << ") e ("<< jackTop <<", " << jackBottom << endl;
            // cout << "Box: ("<< boxLeft <<", " << boxRight << ") e ("<< boxTop <<", " << boxBottom << endl;

            return true;
        } else {
            // Nothing to do
        }
    }

    return false;
}

bool Game::isGameFinished() {
    return this->quitGame;
}

bool Game::isLevelFinished() {
    return this->quitLevel;
}