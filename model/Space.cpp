#include "Space.h"

Space::Space(int id,Marker* m){
    space_id_ = id;
    marker_ = m;
}

int Space::GetSpaceId() const {
    return space_id_;
}

Marker* Space::GetMarker() const {
    return marker_;
}

void Space::SetMarker(Marker *marker) {
    marker_ = marker;
}

/**
 * Check if the space is empty and this function return a boolean
 * @param space analyze this space
 * @return is_empty true if there no markers in this space, else false
 */
bool Space::IsEmpty(){
    return marker_ == nullptr;
}

/**
 * Search all correct moves
 * @param marker_here marker is in this space
 * @return all moves possible for the player, within -1 for impossible choices
 *		   and id_space for
 */
vector<int> Space::GetValidMoves(vector<Space> *spaces){

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
    id_space_enable[0] = space_id_ - 6;
    id_space_enable[1] = space_id_ - 5;
    id_space_enable[2] = space_id_ - 4;
    id_space_enable[3] = space_id_ - 1;
    id_space_enable[4] = space_id_ + 1;
    id_space_enable[5] = space_id_ + 4;
    id_space_enable[6] = space_id_ + 5;
    id_space_enable[7] = space_id_ + 6;

    if(space_id_ >=1 && space_id_ <= 5){ // top

        /* Impossible choices */
        id_space_enable[0] = -1;
        id_space_enable[1] = -1;
        id_space_enable[2] = -1;

    }
    if(space_id_ >=21 && space_id_ <= 25){ //bottom

        /* Impossible choices */
        id_space_enable[5] = -1;
        id_space_enable[6] = -1;
        id_space_enable[7] = -1;

    }
    if(space_id_%5 == 1){ // left

        /* Impossible choices */
        id_space_enable[0] = -1;
        id_space_enable[3] = -1;
        id_space_enable[5] = -1;

    }
    if(space_id_%5 == 0){ // right

        /* Impossible choices */
        id_space_enable[2] = -1;
        id_space_enable[4] = -1;
        id_space_enable[7] = -1;
    }

    /* Check if spaces is empty */
    for(int i = 0; i < 8; i++){
        if(id_space_enable[i] != -1){
            if(!spaces[id_space_enable[i] - 1].IsEmpty()){
                id_space_enable[i] = -1; /* There is a marker on this space */
            }
        }
    }

    return id_space_enable;

}