#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

class material;

struct hitRecord{
    double t;
    vec3 p;
    vec3 normal;
    vec3 color;
    material *matPtr;
};

class hitable {
    public:
        virtual bool hit(const ray& ray, double tMin, double tMax, hitRecord& rec) const = 0;
};

#endif