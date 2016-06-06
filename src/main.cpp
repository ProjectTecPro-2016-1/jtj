#include <iostream>
#include "game.hpp"

using namespace std;


int main() {
    Game game;
    game.init();
    game.loop();
    game.shutdown();

    return 0;
}

