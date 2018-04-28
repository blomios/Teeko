#ifndef TEEKO_SPACE_H
#define TEEKO_SPACE_H

#include "Marker.h"

class Space {
private:
    int space_id_;
    Marker* marker_;
public:
    Space(int id,Marker* m){
        space_id_ = id;
        marker_ = m;
    }

    int getSpace_id() const;
    Marker* getMarker() const;

    void setMarker(Marker* marker);
};


#endif //TEEKO_SPACE_H
