#include "Marker.h"
#include <utility>

/**
 * Marker constructor
 * @param color of the marker
 * @param marker's ID
 */
Marker::Marker(string color, int id) {
    is_selected_ = false;
    color_ = std::move(color);
    marker_id_ = id;
}

int Marker::GetMarkerId() const {
    return marker_id_;
}

string Marker::GetColor() {
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