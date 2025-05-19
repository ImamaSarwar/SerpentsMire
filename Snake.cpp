#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Snake.h"
#include "SnakeSegment.h"
#include "SnakeSpeed.h"
using namespace std;
void Snake::welcomeScreen() {
    sf::Sprite snakeBackgroundSprite;
    sf::Texture snakeBackgroundTexture;
    snakeBackgroundTexture.loadFromFile("snakeBG.png");
    snakeBackgroundSprite.setTexture(snakeBackgroundTexture);
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("Press any key to continue...");
    welcomeText.setCharacterSize(70);
    welcomeText.setPosition(440, 800);
    welcomeText.setFillColor(sf::Color::White);
    sf::Text gameText;
    gameText.setFont(font);
    gameText.setString("Welcome to");
    gameText.setCharacterSize(90);
    gameText.setPosition(550, 20);
    gameText.setFillColor(sf::Color::Black);
    sf::Text nameText;
    nameText.setFont(font);
    nameText.setString("Serpent's Mire!");
    nameText.setCharacterSize(90);
    nameText.setPosition(520, 120);
    nameText.setFillColor(sf::Color::Black);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            // Check if any key is pressed
            if (event.type == sf::Event::KeyPressed) {
                return; //Exit the welcome screen
            }
        }

        window.clear();
        window.draw(snakeBackgroundSprite);
        window.draw(welcomeText);
        window.draw(gameText);
        window.draw(nameText);
        window.display();
    }
}

void Snake::endGame()
{
    sound.playLoseMusic();
    sf::Sprite endGameSprite;
    sf::Texture endGameTexture;
    endGameTexture.loadFromFile("SnakeLose.jpg");
    endGameSprite.setTexture(endGameTexture);
    sf::Text endGameText;
    endGameText.setFont(font);
    endGameText.setString("You Lost!");
    endGameText.setCharacterSize(190);
    endGameText.setPosition(430, 390);
    endGameText.setFillColor(sf::Color::White);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }
        window.clear();
        window.draw(endGameSprite);
        window.draw(endGameText);
        window.display();
    }
}

void Snake::pauseGame()
{
    sf::Sprite pauseSprite;
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("SnakeGame.jpg");
    pauseSprite.setTexture(pauseTexture);

    sf::Text keyText, pauseText, resetGameText;

    keyText.setFont(font);
    keyText.setString("Press esc to resume...");
    keyText.setCharacterSize(60);
    keyText.setPosition(490, 830);
    keyText.setFillColor(sf::Color::White);

    pauseText.setFont(font);
    pauseText.setString("Game Paused");
    pauseText.setCharacterSize(150);
    pauseText.setPosition(400, 350);
    pauseText.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return;
                }

            }
        }
        window.clear();
        window.draw(pauseSprite);
        window.draw(pauseText);
        window.draw(keyText);
        window.display();
    }
}

void Snake::startGame()
{
    welcomeScreen();
    selectLevel();
    int speed;
    sp.setSpeed(level);
    const int windowWidth = 1500;
    const int windowHeight = 960;
    // Initial direction
    int dirX = 1, dirY = 0; // Right

    char scoreBuffer[12];
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle key presses
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W && dirY == 0)
                {
                    dirX = 0; dirY = -1; // Up
                }
                else if (event.key.code == sf::Keyboard::A && dirX == 0)
                {
                    dirX = -1; dirY = 0; // Left
                }
                else if (event.key.code == sf::Keyboard::S && dirY == 0)
                {
                    dirX = 0; dirY = 1; // Down
                }
                else if (event.key.code == sf::Keyboard::D && dirX == 0)
                {
                    dirX = 1; dirY = 0; // Right
                }
                else if (event.key.code == sf::Keyboard::P)
                {
                    pauseGame();
                }
            }
        }

        sp.setTimeSinceLastMove();
        if (sp.getTimeSinceLastMove() >= sp.getSpeed())
        {
            sp.resetTime();

            // Update snake's body
            for (int i = sg.snakeLength - 1; i > 0; --i)
            {
                sg.setsnakeX(i);
                sg.setsnakeY(i);
            }

            sg.setHead(dirX, dirY);
            // game lost
            if (sg.getSnakeX(0) > windowWidth || sg.getSnakeX(0) < -2 || sg.getSnakeY(0) > windowHeight || sg.getSnakeY(0) < -2)
            {

                endGame();
            }

            // Check for snake collision with itself
            for (int i = 1; i < sg.snakeLength; i++)
            {
                if (sg.getSnakeX(0) == sg.getSnakeX(i) && sg.getSnakeY(0) == sg.getSnakeY(i))
                {
                    endGame(); // End the game
                }
            }
            if (sg.getSnakeX(0) < f.getFoodX() + 26 && sg.getSnakeX(0) + 26 > f.getFoodX() && sg.getSnakeY(0) < f.getFoodY() + 32 && sg.getSnakeY(0) + 32 > f.getFoodY())
            {
                if (sg.snakeLength < 300)
                {
                    ++sg.snakeLength;
                }
                f.regenerateApple();
                s.setScore(getLevel());
                s.intToString(scoreBuffer);
                s.scoreText.setString("Score: ");
                s.scoreText.setString(s.scoreText.getString() + scoreBuffer);
                sound.playActionMusic();
            }

            if (currentThresholdIndex < numThresholds && s.getScore() >= easterEggThresholds[currentThresholdIndex] && !f.getActiveState())
            {
                cout << "Generating Easter Egg!" << endl;
                f.generateEasterEgg();

                // Move to the next threshold
                currentThresholdIndex++;
            }
            if (f.getActiveState() && sg.getSnakeX(0) >= f.getEasterX() && sg.getSnakeX(0) < (f.getEasterX() + 89) && sg.getSnakeY(0) >= f.getEasterY() && sg.getSnakeY(0) < (f.getEasterY() + 88)) {

                // Collision detected, reset Easter Egg
                sound.plyEasterEggMusic();
                f.resetEasterEgg();

                sg.snakeLength -= 5; // Increase snake length
                s.setScore(4);       // Increment score by 50
                s.intToString(scoreBuffer);
                s.scoreText.setString("Score: ");
                s.scoreText.setString(s.scoreText.getString() + scoreBuffer);
            }

            // Update snake sprite positions
            for (int i = 0; i < sg.snakeLength; i++)
            {
                sg.snakeSprite[i].setPosition(sg.getSnakeX(i), sg.getSnakeY(i));
            }
        }

        // Render
        window.clear();
        window.draw(snakeBackgroundSprite);
        for (int i = 0; i < sg.snakeLength; i++)
        {
            window.draw(sg.snakeSprite[i]);
        }
        window.draw(s.scoreText);
        window.draw(f.foodSprite);
        if ((f.getActiveState()))
        {
            window.draw(f.easterEggSprite);
        }

        window.display();
    }
}

void Snake::selectLevel() {
    sf::Text title, slug, worm, python;
    title.setFont(font);
    title.setString("Select a Level:");
    title.setCharacterSize(90);
    title.setPosition(510, 250);
    title.setFillColor(sf::Color::Black);

    slug.setFont(font);
    slug.setString("Press S for slug");
    slug.setCharacterSize(60);
    slug.setPosition(560, 400);
    slug.setFillColor(sf::Color::Black);

    worm.setFont(font);
    worm.setString("Press W for Worm");
    worm.setCharacterSize(60);
    worm.setPosition(550, 500);
    worm.setFillColor(sf::Color::Black);

    python.setFont(font);
    python.setString("Press P for Python");
    python.setCharacterSize(60);
    python.setPosition(530, 600);
    python.setFillColor(sf::Color::Black);

    window.draw(title);
    window.draw(slug);
    window.draw(worm);
    window.draw(python);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    setLevel(1);
                    return;
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    setLevel(2);
                    return;
                }
                else if (event.key.code == sf::Keyboard::P)
                {
                    setLevel(3);
                    return;
                }
            }
        }
        window.draw(snakeBackgroundSprite);
        window.draw(title);
        window.draw(slug);
        window.draw(worm);
        window.draw(python);
        window.display();
        window.clear();
    }
}

int main()
{
    srand(time(0));

    Snake s;
    s.window.setPosition(sf::Vector2i(550, 200));
    s.startGame();

    while (s.window.isOpen()) {
        s.window.clear();
        s.window.draw(s.snakeBackgroundSprite);
        s.window.display();
    }
}
