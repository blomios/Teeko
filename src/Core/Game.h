#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H

#include "../AI/AI.h"
#include "../Sound/SoundManager.h"
#include <SFML/System/Thread.hpp>
#include <vector>
#include <algorithm>
#include <thread>

class Game {
public:
    Game(bool is_ai, int difficulty, bool spectator_mode);
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
    void SpectatorLoop();
    SoundManager *GetSoundManager();
    bool IsSpectatorGame();
private:
    vector<Space> spaces_;
    vector<Marker> markers_;
    vector<Player*> players_;
    int turn_; // Player 1 or 2
    int turn_number_;
    Player* winner_ = nullptr;
    bool ai_game_;
    SoundManager sound_manager_;
    bool spectator_mode_;
};

#endif //TEEKO_GAME_H
