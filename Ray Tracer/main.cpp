#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <string>
#include "./CPP/Headers/class.h"
#include "./CPP/Headers/input.h"
#include "./CPP/Headers/sphere.h"
#include "./CPP/Headers/hitable_list.h"
#include "./CPP/Headers/camera.h"
#include "./CPP/Headers/material.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;

const int PIXEL_SAMPLE_AMOUNT = 2;
const int MAX_BOUNCE = 3;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> distr(-1.0, 1.0); // Random number between -1.0 and 1.0

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Application"); 

int test = 0;

const int NUM_BALLS = 4;

const int SAMPLE_SIZE = 10;
int frameCountX = 0;
int frameCountY = 0;

double fpsTimer = 0;

vec3 color(const ray& r, hitable* world, int depth){
    hitRecord rec;
    if(world->hit(r, 0.001, HUGE_VAL, rec) && depth < MAX_BOUNCE){
        ray scattered;
        vec3 attenuation;
        if(rec.matPtr->scatter(r, rec, attenuation, scattered)){
            return attenuation*color(scattered, world, depth+1);
        }else{
            return vec3(0,0,0);
        }
    }else{
        vec3 unitDir = unit_vector(r.direction());
        double t = 0.5*(unitDir.y() + 1.0);
        return t*vec3(1.0, 1.0, 1.0) + (1-t)*vec3(0.1, 0.2, 1);
    }
}

int main(){
    vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3 horizonal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hitable *list[NUM_BALLS];
    list[0] = new sphere(vec3(0,100.5,-1), 100, new diffuse(vec3(1,0,0)));

    for(int i = 1; i < NUM_BALLS; i++){
        vec3 randomColor((distr(gen)+1)/2, (distr(gen)+1)/2, (distr(gen)+1)/2);

        if(distr(gen) > 0){
            list[i] = new sphere(vec3(i*1.1 - NUM_BALLS/2, 0, -1), 0.5, new diffuse(randomColor));
        }else{
            list[i] = new sphere(vec3(i*1.1 - NUM_BALLS/2, 0, -1), 0.5, new metal(randomColor));
        }
    }

    hitable *world = new hitableList(list, NUM_BALLS);

    camera cam;

    window.setFramerateLimit(60);

    sf::RenderTexture rayTracerTexture;
    if (!rayTracerTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cerr << "Failed to create RenderTexture!" << std::endl;
        return -1;
    }

    sf::Sprite rayTracerSprite(rayTracerTexture.getTexture());

    sf::Font font;
    if (!font.loadFromFile("pixel.ttf"))
        return -1;

    sf::Clock clock;
    double deltaTime = 0;
    double framesPerSecond = 100000;

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(20, 10);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                handleKeyDown(window, event, cam, rayTracerTexture);

            if (event.type == sf::Event::KeyReleased)
                handleKeyUp(event);
        }

        updateMousePos(window);
        handleKeyHeld(cam);
        deltaTime = clock.restart().asSeconds();
        framesPerSecond = 1 / deltaTime;
        fpsTimer += deltaTime;

        for (int i = frameCountX; i < SCREEN_WIDTH; i += SAMPLE_SIZE) {
            for (int j = frameCountY; j < SCREEN_HEIGHT; j += SAMPLE_SIZE) {

                vec3 col(0,0,0);
                for(int e = 0; e < PIXEL_SAMPLE_AMOUNT; e++){
                    double u = (double)(i + distr(gen)) / SCREEN_WIDTH;
                    double v = (double)(j + distr(gen)) / SCREEN_HEIGHT;
                    ray r = cam.getRay(u, v);
                    col += color(r, world, 0);
                }

                col /= PIXEL_SAMPLE_AMOUNT;

                sf::RectangleShape rectangle(sf::Vector2f(1, 1));
                rectangle.setPosition(i, j);
                rectangle.setFillColor(sf::Color(sqrt(col[0]) * 255, sqrt(col[1]) * 255, sqrt(col[2]) * 255));
                rayTracerTexture.draw(rectangle);
            }
        }

        rayTracerTexture.display();

        if(fpsTimer >= 1){
            fpsText.setString("FPS: " + std::to_string((int)framesPerSecond));
            fpsTimer = 0;
        }

        window.clear(sf::Color::Transparent);
        window.draw(rayTracerSprite);
        window.draw(fpsText);
        window.display();

        frameCountX++;
        if(frameCountX > SAMPLE_SIZE-1){
            frameCountX = 0;
            frameCountY++;
        }

        if(frameCountY > SAMPLE_SIZE-1)
            frameCountY = 0;
    }
}