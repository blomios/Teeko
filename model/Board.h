#ifndef TEEKO_BOARD_H
#define TEEKO_BOARD_H

#include <vector>
#include "Space.h"
#include "Marker.h"

class Board {
private:
    std::vector<Space> spaces_;
    std::vector<Marker> markers_;

public:
    const std::vector<Space> &getSpaces() const;
};


#endif //TEEKO_BOARD_H
