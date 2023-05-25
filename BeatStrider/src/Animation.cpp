#include "Animation.h"

Animation::Animation(const std::string& filePath, int no_frames, int width, int height)
{
    m_texture.loadFromFile(filePath);

    for (int i = 0; i < no_frames; ++i)
    {
        m_frames.push_back(sf::IntRect(i * width, 0, height, height));
    }
}

void Animation::Update()
{
    float frame_delay = 0.1f;

    if (m_animation_clock.getElapsedTime().asSeconds() > frame_delay)
    {
        m_animation_clock.restart();
        m_current_frame = (m_current_frame + 1) % m_frames.size();
    }
}

sf::Texture& Animation::GetTexture()
{
    return m_texture;
}

sf::IntRect& Animation::GetIntRect()
{
    return m_frames[m_current_frame];
}

AnimationByTextures::AnimationByTextures(std::vector<sf::Texture> frames, float frame_delay)
    : m_frames(frames), m_frame_delay(frame_delay)
{   
}

void AnimationByTextures::Update()
{
    if (m_animation_clock.getElapsedTime().asSeconds() > m_frame_delay)
    {
        m_animation_clock.restart();
        m_current_frame++;

        if (m_current_frame >= m_frames.size())
        {
            m_current_frame = 0;
        }
    }
}

sf::Texture& AnimationByTextures::GetTexture()
{
    return m_frames[m_current_frame];
}
