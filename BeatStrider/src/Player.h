#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"

#include <string>

enum class PlayerState
{
    IDLE,
    RUN,
    JUMP,
};

class Player
{
public:
    Player(const std::string& idle_texture, const std::string& run_texture);
        
    sf::FloatRect GetGlobalBounds();

    void SetCanJump(bool is_can);
    void UpdateJump(const sf::Time& delta);

    void Inputs(const sf::Time& delta, const sf::Time& elapsed);

    void Update(const sf::Time& delta, const sf::Time& elapsed);
    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetVelocity();

private:
    // forces relative to time in ms

    sf::Sprite m_sprite;
    sf::Vector2f m_velocity{ 0.0f, 0.0f };

    Animation m_idle_anim;
    Animation m_run_anim;

    const int m_no_frames = 4;
    int m_current_frame = 0;

    PlayerState m_state;

    std::vector<sf::IntRect> m_idle_frames;
    std::vector<sf::IntRect> m_run_frames;

    sf::Clock m_animation_clock;

    float m_gravity = 0.98f;

    float m_moving_speed = 0.5f;
public:
    bool m_jump = false;
private:
    bool m_can_jump = true;
    int m_jumpforce = -55;

    float m_jumpDelay = 250.0f;
    float m_jumpDelayTimer = 0.0f;
};