#ifndef TEEKO_GAME_H
#define TEEKO_GAME_H

#include "../AI/AI.h"
#include "../Sound/SoundManager.h"
#include <SFML/System/Thread.hpp>
#include <vector>
#include <algorithm>
#include <thread>

/**
 * @brief The main class for the game
 */
class Game {
private:
    // The spaces of the board
    vector<Space> spaces_;
    // The markers of the game
    vector<Marker> markers_;
    // The two players
    vector<Player *> players_;
    // 0 if it's Red's turn, 1 if it's Black's turn
    int turn_;
    // Starts at 1, +1 at each player's turn
    int turn_number_;
    // The winner of the game
    Player *winner_ = nullptr;
    // True if it's an AI game
    bool ai_game_;
    // The sound manager to plays the markers' sounds and victory tone
    SoundManager sound_manager_;
    // True if spectator mode is enabled
    bool spectator_mode_;
public:
    // Constructor
    Game(bool is_ai, int difficulty, bool spectator_mode);

    // Places a marker on the space for a specific player
    void PlaceMarker(Space space, int player);

    // Moves a player's marker from a space to another
    void MoveMarker(Space current_space, Space next_space, int player);

    // Gets the players of the game
    vector<Player *> *GetPlayers();

    // Gets the spaces of the game
    vector<Space> *GetSpaces();

    // Gets the turn number
    int GetTurnNumber();

    // Returns 0 (Red) or 1 (Black) depending on which player it is the turn
    int GetPlayerTurn();

    // Returns a pointer to the winner of the game, else retuns nullptr
    Player *GetWinner();

    // Returns true if the game is opposing a player to an AI
    bool IsAIGame();

    // Main loop for the AI
    void AiLoop();

    // Main loop for the spectator mode
    void SpectatorLoop();

    // Returns the sound manager of the game
    SoundManager *GetSoundManager();

    // Returns true if the game is opposing two AIs
    bool IsSpectatorGame();
};

#endif //TEEKO_GAME_H
