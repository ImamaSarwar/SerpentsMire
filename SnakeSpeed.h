#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class SnakeSpeed {
    float speed;
    float timeSinceLastMove;
public:
    SnakeSpeed() :speed(0), timeSinceLastMove(0.0f) {};

    sf::Clock clock;
    void setSpeed(int level)
    {
        if (level == 1) {
            speed = 0.1f; // Slug

        }
        else if (level == 2) {
            speed = 0.07f; // Worm

        }
        else if (level == 3) {
            speed = 0.05f; // Python

        }
    }
    void setTimeSinceLastMove() {
        timeSinceLastMove += clock.restart().asSeconds();
    }
    void resetTime()
    {
        timeSinceLastMove = 0.0f;
    }
    float getSpeed() const
    {
        return speed;
    }
    float getTimeSinceLastMove() const
    {
        return timeSinceLastMove;
    }

};