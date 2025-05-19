#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class Scores {
    int score = 0;
public:
    sf::Text scoreText;
    sf::Font font;
    Scores() {
        if (!font.loadFromFile("Fonts/virgo.ttf"))
        {
            cout << "Failed to load font!" << endl;
        }
        scoreText.setFont(font);
        scoreText.setCharacterSize(24); // Font size
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10); // Top-left corner
        scoreText.setString("Score: 0"); // Initial score display
    }
    void setScore(int level)
    {
        switch (level)
        {
        case 0:
            score = 0;
            break;
        case 1:
            score += 30;
            break;
        case 2:
            score += 20;
            break;
        case 3:
            score += 10;
            break;
        case 4: //for easter
            score += 50;
            break;
        }
    }
    int getScore()
    {
        return score;
    }
    void intToString(char* buffer) {
        int number = score;
        int index = 0;
        bool isNegative = false;

        // Handle negative numbers
        if (number < 0) {
            isNegative = true;
            number = -number;
        }

        // Extract digits from the number
        do {
            buffer[index++] = '0' + (number % 10);
            number /= 10;
        } while (number > 0);

        // Add negative sign if necessary
        if (isNegative) {
            buffer[index++] = '-';
        }

        // Reverse the buffer to get the correct order
        for (int i = 0; i < index / 2; i++) {
            char temp = buffer[i];
            buffer[i] = buffer[index - 1 - i];
            buffer[index - 1 - i] = temp;
        }

        // Null-terminate the string
        buffer[index] = '\0';
    }

};