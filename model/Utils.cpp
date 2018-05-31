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