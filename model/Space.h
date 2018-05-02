#ifndef TEEKO_SPACE_H
#define TEEKO_SPACE_H

#include "Marker.h"

class Space {
private:
    int space_id_;
    bool isSelected;
    Marker* marker_;
public:
    Space(int id,Marker* m);
    int getSpace_id() const;
    Marker* getMarker() const;
    void setMarker(Marker* marker);
    void Select();
    void Unselect();
};


#endif //TEEKO_SPACE_H
