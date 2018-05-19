#include "Game.h"
using namespace std;

Game::Game(bool is_ai){
    ai_game_ = is_ai;
}
/**
 * Initiation Spaces and Markers
 */
void Game::initGame() {

    for(int i = 0; i < 25; i++){
        this->spaces_.push_back(*(new Space(i+1,NULL)));
    }

    for(int i = 0; i < 8; i++){

        if(i % 2){
            this->markers_.push_back(*(new Marker("Black",i+1)));
        } else {
            this->markers_.push_back(*(new Marker("Red",i+1)));
        }

    }

    this->players_.push_back(*(new Player("Black")));
    this->players_.push_back(*(new Player("Red")));
    this->turn_number_ = 1;
    this->turn_ = 1; // Player Black Start the game
}

/**
 * Search all correct moves
 * @param marker_here marker is in this space
 * @return all moves possible for the player, within -1 for impossible choices
 *		   and id_space for
 */
vector<int> Game::allCorrectMoves(Space marker_here){

    /* First, if the space is next to the marker before the move
     * Next, we check if the space is empty
     *
     * For example : e = empty and M = Marker
     *
     * e | e | e
     * e | M | e
     * e | e | e
     *
     */

    int id_space = marker_here.GetSpaceId();
    vector<int> id_space_enable (8);

    /* 5 cases :
     *
     * Space on the left
     * Space on the right
     * Space on the top
     * Space on the bottom
     * Normal case
     *
     * How to find space_id of spaces choices
     *
     * -6 (0) | -5 (1) | -4 (2)
     * -1 (3) |    x   | +1 (4)
     * +4 (5) | +5 (6) | +6 (7)
     *
     */

    /* Choices */
    id_space_enable[0] = id_space - 6;
    id_space_enable[1] = id_space - 5;
    id_space_enable[2] = id_space - 4;
    id_space_enable[3] = id_space - 1;
    id_space_enable[4] = id_space + 1;
    id_space_enable[5] = id_space + 4;
    id_space_enable[6] = id_space + 5;
    id_space_enable[7] = id_space + 6;

    if(id_space >=1 && id_space <= 5){ // top

        /* Impossible choices */
        id_space_enable[0] = -1;
        id_space_enable[1] = -1;
        id_space_enable[2] = -1;

    }
    if(id_space >=21 && id_space <= 25){ //bottom

        /* Impossible choices */
        id_space_enable[5] = -1;
        id_space_enable[6] = -1;
        id_space_enable[7] = -1;

    }
    if(id_space%5 == 1){ // left

        /* Impossible choices */
        id_space_enable[0] = -1;
        id_space_enable[3] = -1;
        id_space_enable[5] = -1;

    }
    if(id_space%5 == 0){ // right

        /* Impossible choices */
        id_space_enable[2] = -1;
        id_space_enable[4] = -1;
        id_space_enable[7] = -1;
    }

    /* Check if spaces is empty */
    for(int i = 0; i < 8; i++){
        if(id_space_enable[i] != -1){
            if(!spaces_[id_space_enable[i] - 1].IsEmpty()){
                id_space_enable[i] = -1; /* There is a marker on this space */
            }
        }
    }

    return id_space_enable;

}

/**
 * The player want to put a marker on the board
 * @param space the place where the player want the marker
 * @param player who play now
 * @return 1 if the player won the game, 0 else
 *
 */
void Game::PlaceMarker(Space space, int player) {

    if(ai_game_ && players_.at(player).GetColor()=="Red")
    {

    }
    else
    {
        if(space.IsEmpty() && players_.at(player).GetSpaces()->size()<4){
            players_.at(player).GetSpaces()->push_back(&spaces_.at(space.GetSpaceId()-1));
            spaces_.at(space.GetSpaceId() - 1).SetMarker(&markers_.at(turn_number_ - 1));
            turn_number_++;
            turn_ = turn_ == 0 ? 1 : 0;

            if(players_.at(player).IsWinner())
                winner_ = &players_.at(player);
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
    if (players_.at(player).GetSpaces()->size() == 4) {

        vector<int> moves = allCorrectMoves(current_space);
        for(int i = 0; i < 8;i++){
            if(moves.at(i) == (next_space.GetSpaceId())){
                valid = 1;
                break;
            }
        }

        if(valid == 1) {
            players_.at(player).GetSpaces()->push_back(&spaces_.at(next_space.GetSpaceId() - 1));
            spaces_.at(next_space.GetSpaceId() - 1).SetMarker(
                    &markers_.at(current_space.GetMarker()->GetMarkerId() - 1));

            // method erase
            spaces_.at(current_space.GetSpaceId() - 1).SetMarker(nullptr);
            vector<Space *> *spaces = players_.at(player).GetSpaces();
            for (int i = 0; i < 4; i++) {
                if (current_space.GetSpaceId() == spaces->at(i)->GetSpaceId()) {
                    players_.at(player).GetSpaces()->erase(spaces->begin() + i);
                }
            }

            turn_number_++;
            turn_ = turn_ == 0 ? 1 : 0;

            if(players_.at(player).IsWinner())
                winner_ = &players_.at(player);
        }
    }
}

vector<Player>* Game::GetPlayers() {
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
