#pragma once

#include <SFML/Audio.hpp>

#include <vector>

class Audio
{
public:
    Audio();
    Audio(const std::string& filePath);

    void loadFromFile(const std::string& filePath);

    void play();
    void pause();
    void setSpeed(float speed);
    void resume();
    void setTimestamp(sf::Time timestamp);

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::Time timestamp;
    float speed;
};
