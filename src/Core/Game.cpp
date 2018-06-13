#include "Game.h"

using namespace std;

/**
 * Constructor for Game
 * @param is_ai, whether it's an AI game or not
 * @param difficulty, 1 = easy, 2 = normal, 3 = hard
 * @param spectator_mode, true if the game is opposing two AIs
 */
Game::Game(bool is_ai, int difficulty, bool spectator_mode) {
    // Initializes the vector of spaces
    for (int i = 0; i < 25; i++) {
        this->spaces_.push_back(*(new Space(i + 1, nullptr)));
    }

    // Initializes the vector of markers (4 Red, 4 Black)
    for (int i = 0; i < 8; i++) {
        if (i % 2) {
            this->markers_.push_back(*(new Marker("Red", i + 1)));
        } else {
            this->markers_.push_back(*(new Marker("Black", i + 1)));
        }
    }

    // Initializes general parameters
    spectator_mode_ = spectator_mode;
    ai_game_ = is_ai;
    turn_number_ = 1;
    turn_ = 1; // Player Black starts the game


    // If it's an AI game then adds an AI to the vector of players, else adds a player
    // If spectator mode is enabled, adds two AIs instead of one
    if (!ai_game_) {
        players_.push_back(new Player("Red"));
        players_.push_back(new Player("Black"));
    } else {
        players_.push_back(new AI(difficulty, "Red"));
        if (spectator_mode_) {
            players_.push_back(new AI(difficulty, "Black"));
            std::thread ai(SpectatorLoop, this);
            ai.detach();
        } else {
            players_.push_back(new Player("Black"));
            std::thread ai(AiLoop, this);
            ai.detach();
        }
    }
}

/**
 * The player want to put a marker on the board
 * @param space the place where the player want the marker
 * @param player who play now
 * @return 1 if the player won the game, 0 else
 *
 */
void Game::PlaceMarker(Space space, int player) {
    // If the passed space is empty and the player doesn't already have 4 placed markers
    if (space.IsEmpty() && players_.at(player)->GetSpaces()->size() < 4) {
        // Adds the space to the player's vector of spaces
        players_.at(player)->GetSpaces()->push_back(&spaces_.at(space.GetSpaceId() - 1));
        // Adds the marker to the space
        spaces_.at(space.GetSpaceId() - 1).SetMarker(&markers_.at(turn_number_ - 1));
        // Plays the marker sound
        sound_manager_.PlayMarkerSound();
        // Checks if player has won
        if (players_.at(player)->IsWinner())
            winner_ = players_.at(player);
        else { // He hasn't : increment turn number and let the other player play
            turn_number_++;
            turn_ = turn_ == 0 ? 1 : 0;
        }
    }
}

/**
 * The player want to move a marker from the currentSpace to the nextSpace
 * @param current_space the place where was the marker
 * @param next_space the place where the player want the marker
 * @param player who play now
 * @return 1 if the player won the game, 0 else
 *
 */
void Game::MoveMarker(Space current_space, Space next_space, int player) {
    int valid = 0;
    // If the player has already placed his 4 markers
    if (players_.at(player)->GetSpaces()->size() == 4) {
        // Checks if the move is valid
        vector<int> moves = current_space.GetValidMoves(&spaces_);
        for (int i = 0; i < 8; i++) {
            if (moves.at(i) == (next_space.GetSpaceId())) {
                valid = 1;
                break;
            }
        }

        // If the move is valid, proceed
        if (valid == 1) {
            // Adds the space to the player's vector of spaces
            players_.at(player)->GetSpaces()->push_back(&spaces_.at(next_space.GetSpaceId() - 1));
            // Adds the marker to the space of destination
            spaces_.at(next_space.GetSpaceId() - 1).SetMarker(
                    &markers_.at(current_space.GetMarker()->GetMarkerId() - 1));

            // Erase method
            // First, remove the marker from the space it was at
            spaces_.at(current_space.GetSpaceId() - 1).SetMarker(nullptr);
            // Retrieves the player's vector of spaces and remove the space where the marker was from the vector
            vector<Space *> *spaces = players_.at(player)->GetSpaces();
            for (int i = 0; i < 4; i++) {
                if (current_space.GetSpaceId() == spaces->at(i)->GetSpaceId()) {
                    players_.at(player)->GetSpaces()->erase(spaces->begin() + i);
                }
            }
            // Plays the marker sound
            sound_manager_.PlayMarkerSound();
            // Checks if player has won
            if (players_.at(player)->IsWinner())
                winner_ = players_.at(player);
            else { // He hasn't : increment turn number and let the other player play
                turn_number_++;
                turn_ = turn_ == 0 ? 1 : 0;
            }
        }
    }
}

/**
 * This is the main loop for the AI
 */
void Game::AiLoop() {
    while (winner_ == nullptr) {
        // If the AI has already placed its 4 markers
        if (turn_ == 0 && players_.at(0)->GetSpaces()->size() == 4) {
            // Vector of 2 space id, the first one is the space id of the marker to move and the second one is the arrival space's id
            vector<int> spaces_id;
            spaces_id = ((AI *) players_.at(0))->FindBestMoveSpacesId(spaces_);
            MoveMarker(spaces_.at(spaces_id.at(0) - 1), spaces_.at(spaces_id.at(1) - 1), 0);
        }
            // If it hasn't place 4 markers yet
        else if (turn_ == 0 && players_.at(0)->GetSpaces()->size() != 4) {
            int space_id = ((AI *) players_.at(0))->FindBestPlacementSpaceId(spaces_);
            PlaceMarker(spaces_.at(space_id - 1), 0);
        }
    }
}

/**
 * Main loop for the spectator mode
 */
void Game::SpectatorLoop() {
    while (winner_ == nullptr) {
        // If the AI has already placed its 4 markers
        if (turn_ == 0 && players_.at(0)->GetSpaces()->size() == 4) {
            // Vector of 2 space id, the first one is the space id of the marker to move and the second one is the arrival space's id
            vector<int> spaces_id;
            spaces_id = ((AI *) players_.at(0))->FindBestMoveSpacesId(spaces_);
            MoveMarker(spaces_.at(spaces_id.at(0) - 1), spaces_.at(spaces_id.at(1) - 1), 0);
        }
            // If it hasn't place 4 markers yet
        else if (turn_ == 0 && players_.at(0)->GetSpaces()->size() != 4) {
            int space_id = ((AI *) players_.at(0))->FindBestPlacementSpaceId(spaces_);
            PlaceMarker(spaces_.at(space_id - 1), 0);
        } else if (turn_ == 1 && players_.at(1)->GetSpaces()->size() == 4) {
            // Vector of 2 space id, the first one is the space id of the marker to move and the second one is the arrival space's id
            vector<int> spaces_id;
            spaces_id = ((AI *) players_.at(1))->FindBestMoveSpacesId(spaces_);
            MoveMarker(spaces_.at(spaces_id.at(0) - 1), spaces_.at(spaces_id.at(1) - 1), 1);
        }
            // If it hasn't place 4 markers yet
        else if (turn_ == 1 && players_.at(1)->GetSpaces()->size() != 4) {
            int space_id = ((AI *) players_.at(1))->FindBestPlacementSpaceId(spaces_);
            PlaceMarker(spaces_.at(space_id - 1), 1);
        }
    }
}

SoundManager *Game::GetSoundManager() {
    return &sound_manager_;
}

bool Game::IsSpectatorGame() {
    return spectator_mode_;
}

vector<Player *> *Game::GetPlayers() {
    return &players_;
}

vector<Space> *Game::GetSpaces() {
    return &spaces_;
}

int Game::GetTurnNumber() {
    return turn_number_;
}

int Game::GetPlayerTurn() {
    return turn_;
}

Player *Game::GetWinner() {
    return winner_;
}

bool Game::IsAIGame() {
    return ai_game_;
}