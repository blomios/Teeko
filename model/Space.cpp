#include "Space.h"

Space::Space(int id,Marker* m){
    space_id_ = id;
    marker_ = m;
}

int Space::GetSpaceId() const {
    return space_id_;
}

Marker* Space::GetMarker() const {
    return marker_;
}

void Space::SetMarker(Marker *marker) {
    marker_ = marker;
}

/**
 * Check if the space is empty and this function return a boolean
 * @param space analyze this space
 * @return is_empty true if there no markers in this space, else false
 */
bool Space::IsEmpty(){
    return marker_ == nullptr;
}