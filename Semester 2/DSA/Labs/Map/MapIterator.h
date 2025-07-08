#pragma once
#include "Map.h"

class MapIterator {
    //DO NOT CHANGE THIS PART
    friend class Map;
private:
    Map& map; 
    int current;

    MapIterator(Map& m); //BC = WC = TC = Θ(1)
public:
    void first(); //BC = WC = TC = Θ(1)
    void next(); //BC = WC = TC = Θ(1)
    TElem getCurrent(); //BC = WC = TC = Θ(1)
    bool valid() const; //BC = WC = TC = Θ(1)
    TElem remove(); //BC = WC = TC = Θ(1)
};
