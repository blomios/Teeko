#ifndef TEEKO_UTILS_H
#define TEEKO_UTILS_H

#include <vector>
#include <cmath>

using namespace std;

class Utils {
public:
    static vector<int> GetPosXY(int spaceId);
    static int GetDistance(int spaceIdA, int spaceIdB);
};


#endif //TEEKO_UTILS_H
