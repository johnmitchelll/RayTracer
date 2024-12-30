#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "./Headers/matrix.h"
#include <random>

std::random_device class_rd;
std::mt19937 class_gen(class_rd());
std::uniform_real_distribution<> class_distr(-1.0, 1.0);

void colorRect(double x, double y, double w, double h, double r, double g, double b, sf::RenderWindow & window){
    sf::RectangleShape rectangle(sf::Vector2f(w, h));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color(r, g, b));
    window.draw(rectangle);
}

void colorCircle(double x, double y, double radius, double r, double g, double b, sf::RenderWindow &window){
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setPosition(x, y);
    circle.setFillColor(sf::Color(r, g, b));
    window.draw(circle);
}

double angleWithXAxis(const double x, const double y) {
    double angle = atan2(x, y);
    return angle + M_PI;
}

vec3 randomPointOnSphere() {
    vec3 p = 2*vec3(class_distr(class_gen), class_distr(class_gen), class_distr(class_gen)) - vec3(1,1,1);
    do{
        p = 2*vec3(class_distr(class_gen), class_distr(class_gen), class_distr(class_gen)) - vec3(1,1,1);
    }while(p.squared_length() >= 1);
    return p;
}