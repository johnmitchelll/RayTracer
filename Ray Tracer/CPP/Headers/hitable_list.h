#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

class hitableList: public hitable{
    public: 
        hitableList() {};
        hitableList(hitable **l, int n) { list = l; listSize = n; }
        virtual bool hit(const ray& ray, double tMin, double tMax, hitRecord& rec) const;
        hitable **list;
        int listSize;
};

bool hitableList::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
    hitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = tMax;
    for (int i = 0; i < listSize; i++){
        if(list[i]->hit(r, tMin, closestSoFar, tempRec)){
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}

#endif