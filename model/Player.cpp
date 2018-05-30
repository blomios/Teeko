#include "Player.h"

Player::Player(string color) {
    color_ = color;
}

string Player::GetColor() {
    return color_;
}

vector<Space *> *Player::GetSpaces() {
    return &spaces_;
}

/**
 * Check if the player win the game in this turn
 * @param player who want if is the winner of the game
 * @return 1 if the player won the game, 0 else
 */
bool Player::IsWinner(){
    int count_mark_square = 1, count_mark_diago_d = 1, count_mark_diago_u = 1, count_mark_colu = 1 , count_mark_line = 1;
    //Check first if there 4 markers on board
    if(spaces_.size() == 4){
        int* markers_ids = new int[4];
        //Get ids
        for(int i = 0; i < 4; i++){
            markers_ids[i] = spaces_.at(i)->GetSpaceId();
        }

        //Sort tab
        sort(markers_ids,markers_ids + 4);

        int space_id = markers_ids[0];


        for(int i = 1; i < 4; i++){

            if((space_id + 1) == markers_ids[i] && (markers_ids[0] + 5) == markers_ids[2]){
                /* Square */
                if(i == 2){
                    space_id++;
                } else {
                    space_id+=4;
                }
                count_mark_square++;
            } else if((space_id + 1) == markers_ids[i] && (space_id % 5 != 0 && space_id + 1 % 5 != 1)){
                /* Line */
                space_id++;
                count_mark_line++;
            } else if((space_id + 5) == markers_ids[i]){
                /* Column */
                space_id+=5;
                count_mark_colu++;
            } else if((space_id + 6) == markers_ids[i]){
                /* Diagonal */
                space_id+=6;
                count_mark_diago_d++;
            } else if ((space_id + 4) == markers_ids[i]){
                /* Diagonal */
                space_id+=4;
                count_mark_diago_u++;
            }
        }

        return count_mark_square == 4 || count_mark_diago_d == 4 || count_mark_line == 4
               || count_mark_colu == 4 ||  count_mark_diago_u == 4;
    }
}

