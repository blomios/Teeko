#include <SFML/System/Thread.hpp>
#include "Game.h"
using namespace std;

Game::Game(bool is_ai, int difficulty) : ai_(difficulty) {
    ai_game_ = is_ai;
    for(int i = 0; i < 25; i++){
        this->spaces_.push_back(*(new Space(i+1,NULL)));
    }

    for(int i = 0; i < 8; i++){

        if(i % 2){
            this->markers_.push_back(*(new Marker("Red",i+1)));
        } else {
            this->markers_.push_back(*(new Marker("Black",i+1)));
        }

    }

    // If it's an AI game then add an AI to the vector of players, else add a player
    if(!is_ai)
        players_.push_back(new Player("Red"));
    else {
        players_.push_back(&ai_);
    }

    players_.push_back(new Player("Black"));
    this->turn_number_ = 1;
    this->turn_ = 1; // Player Black Start the game

    if (ai_game_) {
        std::thread ai(AiLoop, this);
        ai.detach();
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

    /*if(ai_game_ && players_.at(player).GetColor()=="Red")
    {

    }
    else
    {*/
        if(space.IsEmpty() && players_.at(player)->GetSpaces()->size()<4) {
            players_.at(player)->GetSpaces()->push_back(&spaces_.at(space.GetSpaceId()-1));
            spaces_.at(space.GetSpaceId() - 1).SetMarker(&markers_.at(turn_number_ - 1));
            turn_number_++;
            turn_ = turn_ == 0 ? 1 : 0;

            if(players_.at(player)->IsWinner())
                winner_ = players_.at(player);
            sound_manager_.PlayMarkerSound();
        }
    //}
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
    if (players_.at(player)->GetSpaces()->size() == 4) {

        vector<int> moves = current_space.GetValidMoves(&spaces_);
        for(int i = 0; i < 8;i++){
            if(moves.at(i) == (next_space.GetSpaceId())){
                valid = 1;
                break;
            }
        }

        if(valid == 1) {
            players_.at(player)->GetSpaces()->push_back(&spaces_.at(next_space.GetSpaceId() - 1));
            spaces_.at(next_space.GetSpaceId() - 1).SetMarker(
                    &markers_.at(current_space.GetMarker()->GetMarkerId() - 1));

            // method erase
            spaces_.at(current_space.GetSpaceId() - 1).SetMarker(nullptr);
            vector<Space *> *spaces = players_.at(player)->GetSpaces();
            for (int i = 0; i < 4; i++) {
                if (current_space.GetSpaceId() == spaces->at(i)->GetSpaceId()) {
                    players_.at(player)->GetSpaces()->erase(spaces->begin() + i);
                }
            }

            turn_number_++;
            turn_ = turn_ == 0 ? 1 : 0;

            if(players_.at(player)->IsWinner())
                winner_ = players_.at(player);
            sound_manager_.PlayMarkerSound();
        }
    }
}

vector<Player*>* Game::GetPlayers() {
    return &players_;
}

vector<Space> *Game::GetSpaces() {
    return &spaces_;
}

vector<Marker> *Game::GetMarkers() {
    return &markers_;
}

int Game::GetTurnNumber() {
    return turn_number_;
}

int Game::GetPlayerTurn() {
    return turn_;
}

Player* Game::GetWinner() {
    return winner_;
}

bool Game::IsAIGame() {
    return ai_game_;
}

/**
 * This is the main loop for the AI
 */
void Game::AiLoop() {
    while(winner_== nullptr) {
        // If the AI has already placed its 4 markers
        if (turn_ == 0 && players_.at(0)->GetSpaces()->size() == 4) {
            // Vector of 2 space id, the first one is the space id of the marker to move and the second one is the arrival space's id
            vector<int> spaces_id;
            spaces_id = ai_.FindBestMoveSpacesId(spaces_);
            MoveMarker(spaces_.at(spaces_id.at(0) - 1), spaces_.at(spaces_id.at(1) - 1), 0);
        }
        // If it hasn't place 4 markers yet
        else if(turn_ == 0 && players_.at(0)->GetSpaces()->size() != 4) {
            int space_id = ai_.FindBestPlacementSpaceId(spaces_);
            PlaceMarker(spaces_.at(space_id-1), 0);
        }
    }
}

SoundManager *Game::GetSoundManager() {
    return &sound_manager_;
}
