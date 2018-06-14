#ifndef TEEKO_PLAYER_H
#define TEEKO_PLAYER_H

#include <string>
#include "Space.h"
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Class containing the player's data
 */
class Player {
protected:
    // Player's color ("Red" or "Black")
    string color_;
    // Spaces where the player has a marker on
    vector<Space *> spaces_;
public:
    // Constructor
    explicit Player(string color);

    // Returns player's color ("Red" or "Black")
    string GetColor();

    // Returns the spaces where the player has a marker on
    vector<Space *> *GetSpaces();

    // Checks whether the player has won or not
    bool IsWinner();
};


#endif //TEEKO_PLAYER_H
