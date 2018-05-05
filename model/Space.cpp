#include "Space.h"

Space::Space(int id,Marker* m){
    space_id_ = id;
    marker_ = m;
}

int Space::getSpace_id() const {
    return space_id_;
}

Marker* Space::getMarker() const {
    return marker_;
}

void Space::setMarker(Marker* marker) {
    marker_ = marker;
}