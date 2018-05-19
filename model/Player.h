#ifndef TEEKO_PLAYER_H
#define TEEKO_PLAYER_H

#include <string>
#include "Space.h"
#include <vector>
#include <algorithm>

using namespace std;

class Player {
private:
    string color_;
    vector<Space*> spaces_;
public:
    string getColor();
    Player(string color);
    vector<Space *> *getSpaces();
    bool isWinner();
    int getMarkersOnBoard();
};


#endif //TEEKO_PLAYER_H
