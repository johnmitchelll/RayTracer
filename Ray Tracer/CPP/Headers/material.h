#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"
#include "class.h"

vec3 reflect(const vec3& v, const vec3& n){
    return v  - 2*dot(v,n)*n;
}

class material {
    public:
        virtual bool scatter(const ray& rIn, hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};

class diffuse: public material{
    public: 
        diffuse(const vec3& a) { albedo = a; }
        virtual bool scatter(const ray& rIn, hitRecord& rec, vec3& attenuation, ray& scattered) const {
            (void)rIn;
            vec3 target = rec.p + rec.normal + randomPointOnSphere();
            scattered = ray(rec.p, target-rec.p);
            attenuation = albedo;
            return true;
        }

        vec3 albedo;
};

class metal: public material{
    public: 
        metal(const vec3& a) { albedo = a; }
        virtual bool scatter(const ray& rIn, hitRecord& rec, vec3& attenuation, ray& scattered) const {
            vec3 reflected = reflect(unit_vector(rIn.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

        vec3 albedo;
};

#endif