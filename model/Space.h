#ifndef TEEKO_SPACE_H
#define TEEKO_SPACE_H

#include "Marker.h"

class Space {
private:
    int space_id_;
    Marker *marker_;
public:
    int getSpace_id() const;
    Marker* getMarker() const;
};


#endif //TEEKO_SPACE_H
