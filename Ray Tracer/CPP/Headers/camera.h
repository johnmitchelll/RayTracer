#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "matrix.h"
#include "ray.h"
#include "class.h"
#include <cmath>

class camera {
public:
    camera() {
        lowerLeftCorner = vec3(-2.0, -1.0, -1.0);
        horizonal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
        orientation = mat3(1.0);
    }

    ray getRay(double u, double v) {
        return ray(origin, lowerLeftCorner + u * horizonal + v * vertical);
    }

    void rotateYaw(double angle) {
        mat3 yawMatrix(
            cos(angle), 0, sin(angle),
            0, 1, 0,
            -sin(angle), 0, cos(angle)
        );
        orientation = yawMatrix * orientation;
    }

    void rotatePitch(double angle) {
        vec3 right = vec3(orientation[0][0], orientation[1][0], orientation[2][0]); // Extract the right vector
        mat3 pitchMatrix = mat3::rotationAroundAxis(right, angle);
        orientation = pitchMatrix * orientation;
    }

    void moveForward(double distance) {
        vec3 forward = unit_vector(vec3(-orientation[0][2], -orientation[1][2], -orientation[2][2]));
        origin = origin + forward * distance;
    }

    void moveBackward(double distance) {
        vec3 forward = unit_vector(vec3(-orientation[0][2], -orientation[1][2], -orientation[2][2]));
        origin = origin - forward * distance;
    }

    void updateCameraVectors() {
        lowerLeftCorner = orientation * vec3(-2.0, -1.0, -1.0);
        horizonal = orientation * vec3(4.0, 0.0, 0.0);
        vertical = orientation * vec3(0.0, 2.0, 0.0);
    }

    vec3 lowerLeftCorner;
    vec3 horizonal;
    vec3 vertical;
    vec3 origin;
    mat3 orientation; // Orientation matrix for free rotation
};

#endif
