#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H


#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>
#include <algorithm>

class Game {
public:
    Game(bool isIA):iaGame_(isIA){};

    void initGame();

    vector<int> numberMarkerOnBoard();
    int checkEmptySpace(Space space);
    vector<int> allCorrectMoves(Space marker_here);
    void isWinner(Player player);
    void placeMarker(Space space, int player);
    void moveMarker(Space currentSpace,Space nextSpace, int player);
    vector<Player>* getPlayers();
    vector<Space>* GetSpaces();
    vector<Marker>* GetMarkers();
    int GetTurnNumber();
    int GetPlayerTurn();
    Player GetWinner();

private:
    vector<Space> spaces_;
    vector<Marker> markers_;
    vector<Player> players_;
    int turn_; // Player 1 or 2
    int turn_number_;
    Player* winner_ = nullptr;
    bool iaGame_; // Si jamais on veut lancer contre une IA, ça passe à vrai

};

#endif //TEEKO_GAME_H
