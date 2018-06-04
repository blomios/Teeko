//
// Created by blomi on 22/05/2018.
//

#include "Utils.h"
#include <math.h>


bool Utils::isAdjacent(int spaceA, int spaceB){

    int temp= abs(spaceA-spaceB);

    if(getDistance(spaceA,spaceB)==1){
        return true;
    }
    else return false;
}

//bool Utils::isWinner(){
//
//    int count_mark_square = 1, count_mark_diago_d = 1, count_mark_diago_u = 1, count_mark_colu = 1 , count_mark_line = 1;
//    //Check first if there 4 markers on board
//    if(spaces_.size() == 4){
//        int* markers_ids = new int[4];
//        //Get ids
//        for(int i = 0; i < 4; i++){
//            markers_ids[i] = spaces_.at(i)->GetSpaceId();
//        }
//
//        //Sort tab
//        sort(markers_ids,markers_ids + 4);
//
//        int space_id = markers_ids[0];
//
//
//        for(int i = 1; i < 4; i++){
//
//            if((space_id + 1) == markers_ids[i] && (markers_ids[0] + 5) == markers_ids[2]){
//                /* Square */
//                if(i == 2){
//                    space_id++;
//                } else {
//                    space_id+=4;
//                }
//                count_mark_square++;
//            } else if((space_id + 1) == markers_ids[i] && (space_id % 5 != 0 && space_id + 1 % 5 != 1)){
//                /* Line */
//                space_id++;
//                count_mark_line++;
//            } else if((space_id + 5) == markers_ids[i]){
//                /* Column */
//                space_id+=5;
//                count_mark_colu++;
//            } else if((space_id + 6) == markers_ids[i]){
//                /* Diagonal */
//                space_id+=6;
//                count_mark_diago_d++;
//            } else if ((space_id + 4) == markers_ids[i]){
//                /* Diagonal */
//                space_id+=4;
//                count_mark_diago_u++;
//            }
//        }
//
//        return count_mark_square == 4 || count_mark_diago_d == 4 || count_mark_line == 4
//               || count_mark_colu == 4 ||  count_mark_diago_u == 4;
//    }
//
//}

vector<int> Utils::getPosXY(int spaceId){
    vector<int> pos(2);

    pos[1]=ceil((spaceId)/5);
    pos[0]=(spaceId-1)%5+1;

    return pos;
}

int Utils::getDistance(int spaceIdA, int spaceIdB){

    vector<int> posA=getPosXY(spaceIdA);
    vector<int> posB=getPosXY(spaceIdB);

    int dist;

    dist = max(abs(posA[0]-posB[0]),abs(posA[1]-posB[1]))-1;

    return dist;

}