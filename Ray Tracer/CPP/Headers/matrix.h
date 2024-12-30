#ifndef MATRIX_H
#define MATRIX_H

#include "vec3.h"
#include <array>
#include <iostream>
#include <cmath>

class mat3 {
public:
    std::array<std::array<double, 3>, 3> values;

    // Constructor to initialize with zeros
    mat3() {
        for (auto &row : values) {
            row.fill(0.0);
        }
    }

    // Constructor to initialize with identity matrix
    mat3(double diagonal) {
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                values[i][j] = (i == j) ? diagonal : 0.0;
            }
        }
    }

    mat3(double a00, double a01, double a02,
         double a10, double a11, double a12,
         double a20, double a21, double a22) 
    {
        values[0][0] = a00; values[0][1] = a01; values[0][2] = a02;
        values[1][0] = a10; values[1][1] = a11; values[1][2] = a12;
        values[2][0] = a20; values[2][1] = a21; values[2][2] = a22;
    }

    // Access operator
    std::array<double, 3>& operator[](size_t index) {
        return values[index];
    }

    const std::array<double, 3>& operator[](size_t index) const {
        return values[index];
    }

    // Matrix multiplication
    mat3 operator*(const mat3 &other) const {
        mat3 result;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                for (size_t k = 0; k < 3; ++k) {
                    result[i][j] += values[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    // Matrix-vector multiplication
    vec3 operator*(const vec3 &v) const {
        return vec3(
            values[0][0] * v.x() + values[0][1] * v.y() + values[0][2] * v.z(),
            values[1][0] * v.x() + values[1][1] * v.y() + values[1][2] * v.z(),
            values[2][0] * v.x() + values[2][1] * v.y() + values[2][2] * v.z()
        );
    }

    inline static mat3 rotationAroundAxis(const vec3& axis, double angle);

    // Transpose matrix
    mat3 transpose() const {
        mat3 result;
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                result[i][j] = values[j][i];
            }
        }
        return result;
    }

    // Debug print
    void print() const {
        for (const auto &row : values) {
            for (double val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
};

inline mat3 mat3::rotationAroundAxis(const vec3& axis, double angle) {
    vec3 u = unit_vector(axis); // Normalize the axis
    double cosA = cos(angle);
    double sinA = sin(angle);
    double oneMinusCosA = 1.0 - cosA;

    return mat3(
        cosA + u.x() * u.x() * oneMinusCosA, u.x() * u.y() * oneMinusCosA - u.z() * sinA, u.x() * u.z() * oneMinusCosA + u.y() * sinA,
        u.y() * u.x() * oneMinusCosA + u.z() * sinA, cosA + u.y() * u.y() * oneMinusCosA, u.y() * u.z() * oneMinusCosA - u.x() * sinA,
        u.z() * u.x() * oneMinusCosA - u.y() * sinA, u.z() * u.y() * oneMinusCosA + u.x() * sinA, cosA + u.z() * u.z() * oneMinusCosA
    );
}

#endif
