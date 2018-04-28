#include "Space.h"

int Space::getSpace_id() const {
    return space_id_;
}

Marker* Space::getMarker() const {
    return marker_;
}

void Space::setMarker(Marker* marker) {
    marker_ = marker;
}
