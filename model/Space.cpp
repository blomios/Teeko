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

/**
 * Check if the space is empty and this function return a boolean
 * @param space analyze this space
 * @return is_empty true if there no markers in this space, else false
 */
bool Space::isEmpty(){
    return marker_ == nullptr;
}