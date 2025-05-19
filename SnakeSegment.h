#pragma once
#pragma once
#include <iostream>
#include "Food.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class SnakeSegment {
    const int snakePixelX = 26;
    int snakeX[300] = { 0 };
    int snakeY[300] = { 0 };

public:
    sf::Texture snakeTexture;
    sf::Sprite snakeSprite[300];
    int snakeLength = 3;
    SnakeSegment() {
        snakeTexture.loadFromFile("snakeBody.png");
        snakeX[0] = rand() % 1500; // Head position (random)
        snakeY[0] = rand() % 960;
        for (int i = 0; i < 300; i++)
        {
            snakeX[i] = snakeX[0] - i * snakePixelX;
            snakeY[i] = snakeY[0];
            snakeSprite[i].setTexture(snakeTexture);
            snakeSprite[i].setTextureRect(sf::IntRect(0, 0, snakePixelX, 32));
            snakeSprite[i].setPosition(snakeX[i], snakeY[i]);
        }
    }
    int getSnakePixelX() const {
        return snakePixelX;
    }

    int getSnakeX(int i) {
        return snakeX[i];
    }
    int getSnakeY(int i) {
        return snakeY[i];
    }
    void setsnakeX(int i)
    {
        snakeX[i] = snakeX[i - 1];
    }
    void setsnakeY(int i)
    {
        snakeY[i] = snakeY[i - 1];
    }
    void setHead(int dirX, int dirY) {
        snakeX[0] += (dirX * snakePixelX);
        snakeY[0] += (dirY * snakePixelX);
    }

};
