#include "Player.h"

#include <iostream>

Player::Player(const std::string& idle_texture, const std::string& run_texture)
    : m_idle_anim(idle_texture, 4, 32, 32), m_run_anim(run_texture, 6, 32, 32)
{
    m_sprite.setPosition(50.f, 50.f);

    m_sprite.setOrigin(16, 16);
}

sf::FloatRect Player::GetGlobalBounds()
{
    return m_sprite.getGlobalBounds();
}

void Player::SetCanJump(bool is_can)
{
    m_can_jump = is_can;
}

void Player::Update(const sf::Time& delta, const sf::Time& elapsed)
{
    m_idle_anim.Update();
    m_run_anim.Update();

    Inputs(delta, elapsed);

    switch (m_state)
    {
    case PlayerState::IDLE:
    {
        m_sprite.setTexture(m_idle_anim.GetTexture());
        m_sprite.setTextureRect(m_idle_anim.GetIntRect());
        break;
    }
    case PlayerState::RUN:
    {
        m_sprite.setTexture(m_run_anim.GetTexture());
        m_sprite.setTextureRect(m_run_anim.GetIntRect());
        break;
    }
    case PlayerState::JUMP:
    {
        m_sprite.setTexture(m_idle_anim.GetTexture());
        m_sprite.setTextureRect(m_idle_anim.GetIntRect());
        break;
    }
    default:
    {
        break;
    }
    }

    UpdateJump(delta);
    m_sprite.move(m_velocity.x * delta.asSeconds(), m_velocity.y * delta.asSeconds());
}

void Player::Inputs(const sf::Time& delta, const sf::Time& elapsed)
{
    m_state = PlayerState::IDLE;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_state = PlayerState::RUN;
        m_velocity.x -= m_moving_speed * delta.asMilliseconds();
        m_sprite.setScale(-4.f, 4.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_state = PlayerState::RUN;
        m_velocity.x += m_moving_speed * delta.asMilliseconds();
        m_sprite.setScale(4.f, 4.f);
    }
}

void Player::UpdateJump(const sf::Time& delta)
{
    m_velocity.y += m_gravity * delta.asMilliseconds();

    m_jumpDelayTimer += delta.asMilliseconds();

    if ((m_can_jump))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_jump = true;
        }
    }

    if (m_jump)
    {
        if (m_jumpDelayTimer > m_jumpDelay)
        {
            m_velocity.y = m_jumpforce * delta.asMilliseconds();

            m_jumpDelayTimer = 0.0f;
        }

        m_jump = false;
    }
}


void Player::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::Vector2f Player::GetVelocity()
{
    return m_velocity;
}
