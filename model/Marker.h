#ifndef TEEKO_MARKER_H
#define TEEKO_MARKER_H

#include <string>
using namespace std;

class Marker {
private:
    string color_;
    int marker_id_;
public:
    Marker(string color,int id);
    string getColor();
    int getMarker_id() const;
};



#endif //TEEKO_MARKER_H
