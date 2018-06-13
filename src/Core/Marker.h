#ifndef TEEKO_MARKER_H
#define TEEKO_MARKER_H

#include <string>

using namespace std;

/**
 * @brief Marker contains all the information about a marker
 */
class Marker {
private:
    // Color of the marker, "Red" or "Black"
    string color_;
    // Marker's ID, range : 1->8
    int marker_id_;
    // Whether the marker is selected or not, read by the GameRenderer to display the selection indicator
    bool is_selected_;
public:
    // Constructor for Marker
    Marker(string color, int id);

    // Returns the marker's color
    string GetColor();

    // Returns the marker's ID
    int GetMarkerId() const;

    // Selects the marker
    void Select();

    // Unselects the marker
    void Unselect();

    // Checks if the marker is selected
    bool IsSelected();
};

#endif //TEEKO_MARKER_H
