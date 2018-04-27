#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H


#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include <vector>

class Game {
public:
    void initGame();
    void Start();
    const Board &getBoard() const;
    int* numberMarkerOnBoard(Board board);
    int checkEmptySpace(Space space);
    int* allCorrectMoves(Space marker_here);
    int isWinner(Player player);
    void placeMarker();
    void moveMarker();


private:
    Board board_;
    vector<Space> spaces_;
    vector<Marker> markers_;
    vector<Player> players_;
    int turn_; // Player 1 or 2


};

#endif //TEEKO_GAME_H
