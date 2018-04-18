#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H


#include <SFML/Graphics.hpp>
#include "Board.h"

class Game {
public:
    void Start();
    void Loop();
    static void RenderSpacesLinks();

private:
    sf::RenderWindow main_window_;
    Board board_;
    int turn_; // Player 1 or 2
};


#endif //TEEKO_GAME_H
