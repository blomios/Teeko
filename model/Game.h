#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H


#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>

class Game {
public:
    void initGame();
    void Start();
    vector<int> numberMarkerOnBoard();
    int checkEmptySpace(Space space);
    int* allCorrectMoves(Space marker_here);
    int isWinner(Player player);
    void placeMarker(Space space, int player);
    void moveMarker(Space currentSpace,Space nextSpace, int player);
    vector<Player>* getPlayers();
    vector<Space>* GetSpaces();
    vector<Marker>* GetMarkers();

private:
    vector<Space> spaces_;
    vector<Marker> markers_;
    vector<Player> players_;
    int turn_; // Player 1 or 2
    int numberTurn_;


};

#endif //TEEKO_GAME_H
