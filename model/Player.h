#ifndef TEEKO_PLAYER_H
#define TEEKO_PLAYER_H

#include <string>
#include "Space.h"
#include <vector>
using namespace std;

class Player {
private:
    string color_;
    vector<Space*> spaces;
public:
    string getColor();

    Player(string color){
        color_ = color;
    }

    vector<Space *> *getSpaces(){
        return &spaces;
    }

    int getMarkersOnBoard(){
        return getSpaces()->size();
    }

};


#endif //TEEKO_PLAYER_H
