#pragma once

#include "SFML/Graphics.hpp"

#include "Player.h"

#include <vector>
#include <cmath>
#include <iostream>
#include <random>

class Orb {
public:
    Orb(float x, float y, float radius, sf::Color color, float time)
        : m_radius(radius), m_baseColor(color), m_maxTime(time) 
    {
        m_circle.setPosition(x, y);
        m_circle.setRadius(radius);
        m_circle.setFillColor(color);
    }

    sf::FloatRect GetGlobalBounds()
    {
        return m_circle.getGlobalBounds();
    }

    void Update()
    {
        if (m_clock.getElapsedTime().asMilliseconds() > m_maxTime)
        {
            return;
        }

        // subtle animation
        float scale = std::sin(m_clock.getElapsedTime().asSeconds()) * 0.3f + 1.0f;
        m_circle.setScale(scale, scale);

        // subtle color change
        sf::Color newColor = m_baseColor;
        newColor.r += std::rand() % 10 - 5;
        newColor.g += std::rand() % 10 - 5;
        newColor.b += std::rand() % 10 - 5;

        // clamping to valid color range
        newColor.r = std::min(std::max(int(newColor.r), 0), 255);
        newColor.g = std::min(std::max(int(newColor.g), 0), 255);
        newColor.b = std::min(std::max(int(newColor.b), 0), 255);

        m_circle.setFillColor(newColor);
    }

    void Draw(sf::RenderWindow& window) 
    {
        if (m_clock.getElapsedTime().asMilliseconds() <= m_maxTime)
        {
            window.draw(m_circle);
        }
    }

private:
    sf::CircleShape m_circle;

    sf::Clock m_clock;
    float m_maxTime;

    sf::Color m_baseColor;

    float m_radius;
};

template<typename T>
T random_number(int a, int b)
{
    return T(a + (std::rand() % (b - a + 1)));
}

void Seed()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
}

std::vector<Orb> CreateOrbsRandomly(int n)
{
    std::vector<Orb> orbs;

    for (int i = 0; i < n; i++)
    {
        orbs.push_back(Orb(
            random_number<float>(0, 1600), random_number<float>(0, 900),
            random_number<float>(20, 50),
            sf::Color{ random_number<sf::Uint8>(0, 255), random_number<sf::Uint8>(0, 255), random_number<sf::Uint8>(0, 255), random_number<sf::Uint8>(100, 255) },
            50000.0f));
    }

    return orbs;
}

void DrawOrbsRandomly(std::vector<Orb>& orbs, Player& player, sf::RenderWindow& window)
{
    sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    std::cout << orbs.size() << std::endl;

    // Store the index of the orb to be deleted
    int orbToDelete = -1;

    for (size_t i = 0; i < orbs.size(); ++i)
    {
        Orb& orb = orbs[i];

        // Updating orbs
        orb.Update();

        // Hitboxes
        sf::FloatRect bounds = orb.GetGlobalBounds();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (bounds.contains(pos))
            {
                player.m_jump = true;

                // Store the index of the orb to be deleted
                orbToDelete = i;

                break;
            }
        }

        // Draw hitboxes
        sf::RectangleShape boundingBox(sf::Vector2f(bounds.width, bounds.height));
        boundingBox.setPosition(bounds.left, bounds.top);
        boundingBox.setFillColor(sf::Color::Transparent);
        boundingBox.setOutlineColor(sf::Color::Red);
        boundingBox.setOutlineThickness(1.0f);
        window.draw(boundingBox);

        // Draw orbs
        orb.Draw(window);
    }

    // Erase the orb after the loop completes
    if (orbToDelete != -1)
    {
        orbs.erase(orbs.begin() + orbToDelete);

        // Add a new orb to the vector

        orbs.push_back(Orb(
            random_number<float>(0, 1600), random_number<float>(0, 900),
            random_number<float>(20, 50),
            sf::Color{ random_number<sf::Uint8>(0, 255), random_number<sf::Uint8>(0, 255), random_number<sf::Uint8>(0, 255), random_number<sf::Uint8>(100, 255) },
            50000.0f));

        // Update the orbToDelete index
        orbToDelete = -1;
    }
}
