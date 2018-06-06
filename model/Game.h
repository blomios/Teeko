#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H

#include "AI.h"
#include <vector>
#include <algorithm>
#include <thread>

class Game {
public:
    Game(bool is_ai);
    void PlaceMarker(Space space, int player);
    void MoveMarker(Space current_space, Space next_space, int player);
    vector<Player*>* GetPlayers();
    vector<Space>* GetSpaces();
    vector<Marker>* GetMarkers();
    int GetTurnNumber();
    int GetPlayerTurn();
    Player* GetWinner();
    bool IsAIGame();
    AI* GetAi();
    void AiLoop();
private:
    vector<Space> spaces_;
    vector<Marker> markers_;
    vector<Player*> players_;
    AI ai_ = AI(&spaces_, 0);
    int turn_; // Player 1 or 2
    int turn_number_;
    Player* winner_ = nullptr;
    bool ai_game_;
};

#endif //TEEKO_GAME_H
