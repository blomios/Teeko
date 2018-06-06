#include <SFML/System/Thread.hpp>
#include "Game.h"
using namespace std;

Game::Game(bool is_ai, int difficulty) : ai_(&spaces_, difficulty) {
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

AI *Game::GetAi() {
    return &ai_;
}

void Game::AiLoop() {
    while(winner_== nullptr) {
        if (turn_ == 0 && players_.at(0)->GetSpaces()->size() == 4) {
            vector<int> spaces_id;
            spaces_id = ai_.FindBestMoveSpacesId(spaces_);
            //std::cout << "Moving marker on space #" << spaces_id.at(0) << " to #" << spaces_id.at(1) << endl;
            MoveMarker(spaces_.at(spaces_id.at(0) - 1), spaces_.at(spaces_id.at(1) - 1), 0);
        }
        else if(turn_ == 0 && players_.at(0)->GetSpaces()->size() != 4) {
            int rand_space_id = rand()%25;
            while(GetSpaces()->at(rand_space_id).GetMarker() != nullptr)
                rand_space_id = rand()%25;
            PlaceMarker(spaces_.at(rand_space_id), 0);
        }
    }
}
