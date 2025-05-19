#pragma once
#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

class SoundSystem
{
private:
    sf::Music loseMusic;
    sf::Music winMusic;
    sf::Music actionMusic;
    sf::Music easterEggMusic;
public:
    SoundSystem() {
        loseMusic.openFromFile("GameLose.wav");
        winMusic.openFromFile("GameWin.wav");
        actionMusic.openFromFile("action.wav");
        easterEggMusic.openFromFile("easterEgg.wav");
    }

    void playLoseMusic()
    {
        loseMusic.play();
        loseMusic.setVolume(50);
    }

    void playWinMusic()
    {
        winMusic.play();
        winMusic.setVolume(50);
    }

    void playActionMusic()
    {
        actionMusic.play();
        actionMusic.setVolume(50);
    }
    void plyEasterEggMusic()
    {
        easterEggMusic.play();
        easterEggMusic.setVolume(50);
    }
};
