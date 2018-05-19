#ifndef TEEKO_SPACE_H
#define TEEKO_SPACE_H

#include "Marker.h"

class Space {
private:
    int space_id_;
    Marker* marker_;
public:
    Space(int id,Marker* m);
    int GetSpaceId() const;
    Marker* GetMarker() const;
    void SetMarker(Marker *marker);
    bool IsEmpty();
};


#endif //TEEKO_SPACE_H
