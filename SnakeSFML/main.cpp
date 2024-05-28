#include "Game.h"
#include "GameState.h"

int main() {
    Game game("Snake SFML", 800, 800);
    game.setInitialState(new GameState());
    game.run();
                           
    return 0;
}