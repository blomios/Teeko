#ifndef TEEKO_BOARD_H
#define TEEKO_BOARD_H

#include <vector>
#include "Space.h"
#include "Marker.h"

class Board {
private:
    std::vector<Space> spaces_;
    std::vector<Marker> markers_;
};


#endif //TEEKO_BOARD_H
