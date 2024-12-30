#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include "camera.h"

extern sf::Vector2i mousePos;

void handleKeyDown(sf::RenderWindow & window, sf::Event & event, camera & cam, sf::RenderTexture& rtt);
void handleKeyUp(sf::Event & event);
void updateMousePos(sf::RenderWindow & window);
void handleKeyHeld(camera& cam);

#endif