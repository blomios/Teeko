#include <algorithm>
#include "Game.h"
using namespace std;

void Game::Start() {
    this->initGame();

    do{
        this->numberTurn_ += 1;
        if(this->turn_ == 0){
            // Player Black



            this->turn_ = 1;
        } else {
            //Player Red


            this->turn_ = 0;
        }

    }while(isWinner(players_[0]) || isWinner(players_[1]));
}

/**
 * Initiation Spaces and Markers
 */

void Game::initGame() {
    for(int i = 0; i < 25; i++){
        spaces_.push_back(*(new Space(i+1,NULL)));
    }

    for(int i = 0; i < 8; i++){
        if( i < 4){
            markers_.push_back(*(new Marker("Black")));
        } else {
            markers_.push_back(*(new Marker("Red")));
        }

    }

    players_.push_back(*(new Player("Black")));
    players_.push_back(*(new Player("Red")));

    // TODO(anyone) Remove the next two lines, test purpose
    players_.at(1).getSpaces()->push_back(&spaces_.at(2));
    spaces_.at(2).setMarker(&markers_.at(5));

    this->turn_ = 0; // Player Black Start the game
    this->numberTurn_ = 0; // Start turn
}

const Board &Game::getBoard() const {
    return board_;
}
/**
* Count markers on the board
*
* @return number_marker_on_board Number of marker on board for each player
* 0 for the player who plays black markers, 1 for the other player (red)
*/
int* Game::numberMarkerOnBoard(Board board){
    // Check all spaces and return number of marker on the board
    // Count number of marker for each players
    vector<Space> spaces = board.getSpaces();
    Marker* x;
    int* number_marker_on_board;
    for(int i = 0; i < spaces.size() ; i++){
        if ((x = spaces[i].getMarker()) != NULL ){
            if(x->getColor().compare("Black")){
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
    return space.getMarker() == NULL ? 1/*true*/ : 0;
}

/**
 * Search all correct moves
 * @param marker_here marker is in this space
 * @return all moves possible for the player, within -1 for impossible choices
 *		   and id_space for
 */
int* Game::allCorrectMoves(Space marker_here){

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
    int* id_space_enable = new int[8];

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
            if(checkEmptySpace(spaces_[id_space_enable[i]-1])){
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
int Game::isWinner(Player player){
    int winner = 1; /* True */

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

            }else if((space_id + 1) == markers_ids[i]){
                /* Line */
                space_id++;

            } else if((space_id + 5) == markers_ids[i]){
                /* Column */
                space_id+=5;

            } else if((space_id + 6) == markers_ids[i]){
                /* Diagonal */
                space_id+=6;

            } else {
                /* The player doesn't  win this turn */
                winner = 0; /* False */
                break;
            }
        }

        return winner;
    }
    return winner - 1; /* False */
}
/**
 * The player want to put a marker on the board
 *
 *
 */
void Game::placeMarker(Space space, Marker marker) {
    int* movesAvailables=allCorrectMoves(space);

    for(int i=0; i<8; i++) {
        if (movesAvailables[i] == space.getSpace_id()) {
            space.setMarker(&marker);
            return;
        }
    }

}

void Game::moveMarker(Space currentSpace, Space nextSpace) {

    int* movesAvailables=allCorrectMoves(currentSpace);

    for(int i=0; i<8; i++){
        if(movesAvailables[i]==nextSpace.getSpace_id()){

            Marker* currentMarker = currentSpace.getMarker();

            nextSpace.setMarker(currentMarker);
            currentSpace.setMarker(nullptr);

            return;
        }
    }
}

vector<Player>* Game::getPlayers() {
    return &players_;
}

