#include "Utils.h"

vector<int> Utils::GetPosXY(int spaceId){
    vector<int> pos(2);

    pos[1]=ceil((spaceId)/5);
    pos[0]=(spaceId-1)%5+1;

    return pos;
}

int Utils::GetDistance(int spaceIdA, int spaceIdB){

    vector<int> posA= GetPosXY(spaceIdA);
    vector<int> posB= GetPosXY(spaceIdB);

    int dist;

    dist = max(abs(posA[0]-posB[0]),abs(posA[1]-posB[1]))-1;

    return dist;

}