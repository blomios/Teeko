#ifndef TEEKO_PLAYER_H
#define TEEKO_PLAYER_H

#include <string>
#include "Space.h"
#include <vector>
#include <algorithm>

using namespace std;

class Player {
protected:
    string color_;
    vector<Space*> spaces_;
public:
    string GetColor();
    Player(string color);
    vector<Space *> *GetSpaces();
    bool IsWinner();
};


#endif //TEEKO_PLAYER_H
