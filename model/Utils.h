//
// Created by blomi on 22/05/2018.
//

#ifndef TEEKO_UTILS_H
#define TEEKO_UTILS_H

#include <vector>
using namespace std;


class Utils {
public:

    bool static isAdjacent(int spaceA, int spaceB);
    static vector<int> getPosXY(int spaceId);
    static int getDistance(int spaceIdA, int spaceIdB);

};


#endif //TEEKO_UTILS_H
