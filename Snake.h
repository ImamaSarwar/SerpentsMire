#pragma once
//#pragma once
#include <iostream>
#include "Game.h"
#include "SnakeSegment.h"
#include "SnakeSpeed.h"
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

class Snake :public Game
{
    int level;
    const int easterEggThresholds[5] = { 300, 900, 1800, 3300, 5000 }; // Static array for thresholds
    const int numThresholds = 5;
    int currentThresholdIndex = 0;  // Track the current threshold
public:

    SnakeSegment sg;
    Food f;

    SnakeSpeed sp;
    sf::RenderWindow window;
    sf::Texture snakeBackgroundTexture;
    sf::Sprite snakeBackgroundSprite;
    sf::Font font;
    Scores s;

    Snake() : window(sf::VideoMode(1500, 960), "SNAKE", sf::Style::Close | sf::Style::Titlebar)
    {

        snakeBackgroundTexture.loadFromFile("SnakeGame.jpg");
        snakeBackgroundSprite.setTexture(snakeBackgroundTexture);
        if (!font.loadFromFile("Fonts/October Crow.ttf"))
        {
            cout << "Failed to load font!" << endl;
        }
    }

    void setLevel(int l)
    {
        level = l;
    }
    int getLevel()
    {
        return level;
    }
    void welcomeScreen();
    void selectLevel();
    void startGame() override;
    void pauseGame();
    void endGame() override;

};

