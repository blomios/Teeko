#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H

#include "AI.h"
#include "../view/SoundManager.h"
#include <vector>
#include <algorithm>
#include <thread>

class Game {
public:
    Game(bool is_ai, int difficulty);
    void PlaceMarker(Space space, int player);
    void MoveMarker(Space current_space, Space next_space, int player);
    vector<Player*>* GetPlayers();
    vector<Space>* GetSpaces();
    vector<Marker>* GetMarkers();
    int GetTurnNumber();
    int GetPlayerTurn();
    Player* GetWinner();
    bool IsAIGame();
    void AiLoop();
    SoundManager *GetSoundManager();
private:
    vector<Space> spaces_;
    vector<Marker> markers_;
    vector<Player*> players_;
    AI ai_;
    int turn_; // Player 1 or 2
    int turn_number_;
    Player* winner_ = nullptr;
    bool ai_game_;
    SoundManager sound_manager_;

};

#endif //TEEKO_GAME_H
