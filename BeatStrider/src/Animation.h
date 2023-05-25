#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class Animation
{
public:
    Animation(const std::string& filePath, int no_frames, int width, int height);

    void Update();

    sf::Texture& GetTexture();
    sf::IntRect& GetIntRect();

private:
    sf::Texture m_texture;

    sf::Clock m_animation_clock;

    int m_current_frame = 0;
    std::vector<sf::IntRect> m_frames;
};

class AnimationByTextures
{
public:
    AnimationByTextures(std::vector<sf::Texture> frames, float frame_delay);

    void Update();

    sf::Texture& GetTexture();
private:
    std::vector<sf::Texture> m_frames;
    int m_current_frame = 0;

    float m_frame_delay;

    sf::Clock m_animation_clock;
};