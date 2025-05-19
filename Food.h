#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class Food {
    int foodX, foodY;
    int easterEggX, easterEggY;
    bool isEasterEggActive = false;
public:
    sf::Texture foodTexture;
    sf::Sprite foodSprite;
    sf::Texture easterEggTexture;
    sf::Sprite easterEggSprite;
    Food() {
        foodTexture.loadFromFile("snakeFood.jpg");
        foodSprite.setTexture(foodTexture);
        regenerateApple();
    }
    void setEasterEgg()
    {
        isEasterEggActive = true;
    }
    void resetEasterEgg() {
        isEasterEggActive = false; // Deactivate Easter Egg
        easterEggX = -1;     // Move out of bounds
        easterEggY = -1;
        easterEggSprite.setPosition(-50, -50); // Place sprite out of view
    }

    bool getActiveState() {
        return isEasterEggActive;
    }
    int getFoodX() const {
        return foodX;
    }

    int getFoodY() const {
        return foodY;
    }
    int getEasterX()
    {
        return easterEggX;
    }
    int getEasterY()
    {
        return easterEggY;
    }
    void regenerateApple() {
        foodX = (rand() % (1500 / 26)) * 26;
        foodY = (rand() % (960 / 26)) * 26;
        foodSprite.setPosition(foodX, foodY);
    }

    void generateEasterEgg() {
        if (!easterEggTexture.loadFromFile("bigFood.png")) {
            cout << "Error: Could not load Easter Egg texture!" << endl;
            return;
        }
        easterEggSprite.setTexture(easterEggTexture);
        easterEggX = (rand() % (1500 / 26)) * 26;
        easterEggY = (rand() % (960 / 26)) * 26;
        easterEggSprite.setPosition(easterEggX, easterEggY);
        isEasterEggActive = true;
    }

};
