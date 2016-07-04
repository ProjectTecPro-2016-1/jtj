#include <iostream>
#include "game.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    Game game;

    if (argc >= 2) {
    	game.setLanguage(argv[1]);
    } else {
    	game.setLanguage("");
    }

    game.init();
    game.loop();
    game.shutdown();

    return 0;
}

