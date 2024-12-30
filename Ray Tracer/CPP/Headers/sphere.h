#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"

class sphere: public hitable {
    public: 
        sphere() : mat(nullptr) {}
        sphere(vec3 cen, double r, material* m) : center(cen), radius(r), mat(m) {}
        virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const;

        vec3 center;
        double radius;
        material* mat;
};

bool sphere::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - a*c;

    if(discriminant > 0){
        double temp = (-b - sqrt(b*b - a*c)) / a;
        if(tMin < temp && temp < tMax){
            rec.t = temp;
            rec.p = r.pointAtParameter(temp);
            rec.normal = (rec.p - center) / radius;
            rec.matPtr = mat;
            return true;
        }
        temp = (-b + sqrt(b*b - a*c)) / a;
        if(tMin < temp && temp < tMax){
            rec.t = temp;
            rec.p = r.pointAtParameter(temp);
            rec.normal = (rec.p - center) / radius;
            rec.matPtr = mat;
            return true;
        }
    }

    return false;
}

#endif