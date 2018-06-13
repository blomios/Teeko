#ifndef TEEKO_MARKER_H
#define TEEKO_MARKER_H

#include <string>
using namespace std;

class Marker {
private:
    string color_;
    int marker_id_;
    bool is_selected_;
public:
    Marker(string color,int id);
    string GetColor();
    int GetMarkerId() const;
    void Select();
    void Unselect();
    bool IsSelected();
};



#endif //TEEKO_MARKER_H
