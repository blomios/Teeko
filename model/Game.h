#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H


#include <SFML/Graphics.hpp>
#include "Board.h"
#include <vector>

class Game {
public:
    void Start();
    const Board &getBoard() const;
private:
    Board board_;
    int turn_; // Player 1 or 2
};

#endif //TEEKO_GAME_H
