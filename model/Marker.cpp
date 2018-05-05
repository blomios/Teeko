#include "Marker.h"

Marker::Marker(string color,int id){
    is_selected_ = false;
    color_ = color;
    marker_id_ = id;
}

int Marker::getMarker_id() const {
    return marker_id_;
}

string Marker::getColor(){
    return color_;
}

void Marker::Select() {
    this->is_selected_ = true;
}

void Marker::Unselect() {
    this->is_selected_ = false;
}

bool Marker::IsSelected() {
    return is_selected_;
}