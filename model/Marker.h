#ifndef TEEKO_MARKER_H
#define TEEKO_MARKER_H

#include <string>
using namespace std;

class Marker {
private:
    string color_;
public:
    Marker(string color){
        color_ = color;
    }

    string getColor(){
        return color_;
    }
};



#endif //TEEKO_MARKER_H
