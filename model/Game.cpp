#include "Game.h"
using namespace std;


/**
 * Initiation Spaces and Markers
 */
void Game::initGame() {
    this->turn_number_ += 1;
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

    this->turn_ = 0; // Player Black Start the game
    this->turn_number_ = 0; // Start turn
}

/**
* Count markers on the board
*
* @return number_marker_on_board Number of marker on board for each player
* 0 for the player who plays black markers, 1 for the other player (red)
*/
vector<int> Game::numberMarkerOnBoard(){
    // Check all spaces and return number of marker on the board
    // Count number of marker for each players
    Marker* x;
    vector<int> number_marker_on_board;
    for (Space &space : this->spaces_) {
        if ((x = space.getMarker()) != nullptr){
            if(x->getColor()=="Black"){
                number_marker_on_board[0]++;
            } else {
                number_marker_on_board[1]++;
            }
        }
    }
    return number_marker_on_board;
}

/**
 * Check if the space is empty and this function return a boolean
 * @param space analyze this space
 * @return is_empty true if there no markers in this space, else false
 */
int Game::checkEmptySpace(Space space){
    return space.getMarker() == nullptr ? 1/*true*/ : 0;
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

    int id_space = marker_here.getSpace_id();
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
            if(!checkEmptySpace(spaces_[id_space_enable[i]-1])){
                id_space_enable[i] = -1; /* There is a marker on this space */
            }
        }
    }

    return id_space_enable;

}
/**
 * Check if the player win the game in this turn
 * @param player who want if is the winner of the game
 * @return 1 if the player won the game, 0 else
 */
void Game::isWinner(Player player){
    winner_ = &player;
    //Check first if there 4 markers on board
    if(player.getMarkersOnBoard() == 4){
        vector<Space*> *spaces_contains_markers = player.getSpaces();
        int* markers_ids = new int[4];
        //Get ids
        for(int i = 0; i < 4; i++){
            markers_ids[i] = spaces_contains_markers->at(i)->getSpace_id();
        }

        //Sort tab
        sort(markers_ids,markers_ids + 4);

        int space_id = markers_ids[0];


        for(int i = 1; i < 4; i++){

            if((space_id + 1) == markers_ids[i] && (markers_ids[0] + 5) == markers_ids[2]){
                /* Square */
                if(i < 1){
                    space_id++;
                } else {
                    space_id+=4;
                }

            } else if((space_id + 1) == markers_ids[i]){
                /* Line */
                space_id++;

            } else if((space_id + 5) == markers_ids[i]){
                /* Column */
                space_id+=5;

            } else if((space_id + 6) == markers_ids[i]){
                /* Diagonal */
                space_id+=6;

            } else {
                winner_ = nullptr;
            }
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
void Game::placeMarker(Space space, int player) {

    if(iaGame_ && players_.at(player).getColor()=="Red")
    {

    }
    else
    {
        if(checkEmptySpace(space) && players_.at(player).getSpaces()->size()<4){
            players_.at(player).getSpaces()->push_back(&spaces_.at(space.getSpace_id()-1));
            spaces_.at(space.getSpace_id()-1).setMarker(&markers_.at(turn_number_-1));
            turn_number_++;
            turn_ = turn_ == 0 ? 1 : 0;

            isWinner(players_.at(player));
        }
    }
}

/**
 * The player want to move a marker from the currentSpace to the nextSpace
 * @param currentSpace the place where was the marker
 * @param nextSpace the place where the player want the marker
 * @param player who play now
 * @return 1 if the player won the game, 0 else
 *
 */
void Game::moveMarker(Space currentSpace, Space nextSpace, int player) {
    int valid = 0;
    if (players_.at(player).getSpaces()->size() == 4) {

        vector<int> moves = allCorrectMoves(currentSpace);
        for(int i = 0; i < 8;i++){
            if(moves.at(i) == (nextSpace.getSpace_id())){
                valid = 1;
                break;
            }
        }

        if(valid == 1) {
            players_.at(player).getSpaces()->push_back(&spaces_.at(nextSpace.getSpace_id() - 1));
            spaces_.at(nextSpace.getSpace_id() - 1).setMarker(
                    &markers_.at(currentSpace.getMarker()->getMarker_id() - 1));

            // method erase
            spaces_.at(currentSpace.getSpace_id() - 1).setMarker(nullptr);
            vector<Space *> *spaces = players_.at(player).getSpaces();
            for (int i = 0; i < 4; i++) {
                if (currentSpace.getSpace_id() == spaces->at(i)->getSpace_id()) {
                    players_.at(player).getSpaces()->erase(spaces->begin() + i);
                }
            }

            turn_number_++;
            turn_ = turn_ == 0 ? 1 : 0;

            isWinner(players_.at(player));
        }
    }
}

vector<Player>* Game::getPlayers() {
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

Player Game::GetWinner() {
    return *winner_;
}
