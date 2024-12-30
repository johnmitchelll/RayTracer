#include <SFML/Graphics.hpp>
#include <iostream>
#include "./Headers/camera.h"
#include "./Headers/class.h"
#include <cmath>
#include "./Headers/input.h"

sf::Vector2i mousePos;
const int LEFT = 71;
const int RIGHT = 72;
const int UP = 73;
const int DOWN = 74;
const int SPACE = 57;
const int SHIFT = 42;

bool leftHeld = false;
bool rightHeld = false;
bool upHeld = false;
bool downHeld = false;
bool spaceHeld = false;
bool shiftHeld = false;

const double ROTATION_SPEED = 0.04;

void handleKeyDown(sf::RenderWindow & window, sf::Event & event, camera & cam, sf::RenderTexture& rtt){
    rtt.clear();
    if (event.key.code == LEFT) {
        leftHeld = true;
        handleKeyHeld(cam);
    } else if (event.key.code == RIGHT) {
        rightHeld = true;
        handleKeyHeld(cam);
    } else if (event.key.code == UP) {
        upHeld = true;
        handleKeyHeld(cam);
    } else if (event.key.code == DOWN) {
        downHeld = true;
        handleKeyHeld(cam);
    } else if (event.key.code == SPACE) {
        spaceHeld = true;
        handleKeyHeld(cam);
    } else if (event.key.code == SHIFT) {
        shiftHeld = true;
        handleKeyHeld(cam);
    } else if (event.key.code == sf::Keyboard::Escape) {
        window.close();
    }
}

void handleKeyUp(sf::Event & event){
    if (event.key.code == LEFT) {
        leftHeld = false;
    } else if (event.key.code == RIGHT) {
        rightHeld = false;
    } else if (event.key.code == UP) {
        upHeld = false;
    } else if (event.key.code == DOWN) {
        downHeld = false;
    } else if (event.key.code == SPACE) {
        spaceHeld = false;
    } else if (event.key.code == SHIFT) {
        shiftHeld = false;
    }
}

void handleKeyHeld(camera& cam){
    if(leftHeld)
        cam.rotateYaw(ROTATION_SPEED);

    if(rightHeld)
        cam.rotateYaw(-ROTATION_SPEED);

    if(upHeld)
        cam.rotatePitch(-ROTATION_SPEED);

    if(downHeld)
        cam.rotatePitch(ROTATION_SPEED);

    if(spaceHeld)
        cam.moveForward(ROTATION_SPEED);

    if(shiftHeld)
        cam.moveBackward(ROTATION_SPEED);

    cam.updateCameraVectors();
}


void updateMousePos(sf::RenderWindow & window){
    mousePos = sf::Mouse::getPosition(window);
}
