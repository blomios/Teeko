#include "Marker.h"

Marker::Marker(string color,int id){
    color_ = color;
    marker_id_ = id;
}

int Marker::getMarker_id() const {
    return marker_id_;
}

string Marker::getColor(){
    return color_;
}

