#ifndef CLASS_H
#define CLASS_H

#include <SFML/Graphics.hpp>
#include "matrix.h"
#include "vec3.h"

void colorRect(double x, double y, double w, double h, double r, double g, double b, sf::RenderWindow &window);
void colorCircle(double x, double y, double radius, double r, double g, double b, sf::RenderWindow &window);
double angleWithXAxis(double x, double y);
vec3 randomPointOnSphere();

#endif