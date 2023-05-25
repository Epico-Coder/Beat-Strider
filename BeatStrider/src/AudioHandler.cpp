#include "AudioHandler.h"

Audio::Audio() 
    : speed(1.0f) 
{
}

Audio::Audio(const std::string& filePath) 
    : speed(1.0f)
{
    loadFromFile(filePath);
}

void Audio::loadFromFile(const std::string& filePath)
{
    buffer.loadFromFile(filePath);
    sound.setBuffer(buffer);
}

void Audio::play()
{
    sound.play();
}

void Audio::pause()
{
    sound.pause();
}

void Audio::setSpeed(float speed)
{
    this->speed = speed;
    sound.setPitch(speed);
}

void Audio::resume()
{
    sound.play();
}

void Audio::setTimestamp(sf::Time timestamp)
{
    this->timestamp = timestamp;
    sound.setPlayingOffset(timestamp);
}
