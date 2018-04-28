#include "Space.h"

Space::Space(int id,Marker* m){
    isSelected = false;
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

void Space::Select() {
    this->isSelected = true;
}

void Space::Unselect() {
    this->isSelected = false;
}