#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

class RoundedRectangle 
{
public:
    RoundedRectangle(float width, float height, float radius, int points, sf::Vector2f position, sf::Color color) 
    {
        shape.setPosition(position);
        shape.setPointCount(4 * points);
        shape.setFillColor(color);

        const float pi = 3.14159f;

        // Top-left corner
        for (int i = 0; i < points; i++) 
        {
            float angle = (pi / 2) / (points - 1) * i;
            shape.setPoint(i, sf::Vector2f(radius * (1 - cos(angle)), radius * (1 - sin(angle))));
        }

        // Top-right corner
        for (int i = 0; i < points; i++)
        {
            float angle = (pi / 2) / (points - 1) * i;
            shape.setPoint(points + i, sf::Vector2f(width - radius + radius * sin(angle), radius * (1 - cos(angle))));
        }

        // Bottom-right corner
        for (int i = 0; i < points; i++) {
            float angle = (pi / 2) / (points - 1) * i;
            shape.setPoint(2 * points + i, sf::Vector2f(width - radius + radius * cos(angle), height - radius + radius * sin(angle)));
        }

        // Bottom-left corner
        for (int i = 0; i < points; i++) 
        {
            float angle = (pi / 2) / (points - 1) * i;
            shape.setPoint(3 * points + i, sf::Vector2f(radius * (1 - sin(angle)), height - radius + radius * cos(angle)));
        }
    }

    void Draw(sf::RenderWindow& window) 
    {
        window.draw(shape);
    }
private:
    sf::ConvexShape shape;

};

class Notes 
{
public:
    Notes(int maxLines, int displayableLines, float lineWidth, const sf::Vector2f& panelPosition, const sf::Vector2f& panelSize, float velocity)
        : maxLines(maxLines), displayableLines(displayableLines), lineWidth(lineWidth), panelPosition(panelPosition), panelSize(panelSize), velocity(velocity),
        panel(panelSize.x, panelSize.y, 10, 10, panelPosition, sf::Color(31u, 37u, 42u, 255u))
    {
        for (int i = 0; i < maxLines; i++)
        {
            sf::RectangleShape line(sf::Vector2f(lineWidth, panelSize.y));
            line.setPosition(panelPosition.x - (i * panelSize.x / displayableLines), panelPosition.y);
            line.setFillColor(sf::Color(175u, 90u, 90u, 175u));

            lines.push_back(line);
        }
    }

    void Update()
    {
        float deltaTime = clock.restart().asSeconds();

        for (int i = 0; i < maxLines; i++)
        {
            lines[i].setPosition(lines[i].getPosition().x + velocity * deltaTime, lines[i].getPosition().y);
        }
    }

    void Draw(sf::RenderWindow& window) 
    {
        panel.Draw(window);

        for (int i = 0; i < maxLines; i++)
        {
            if ((lines[i].getPosition().x > panelPosition.x) && (lines[i].getPosition().x < panelPosition.x + panelSize.x))
            {
                window.draw(lines[i]);
            }
        }
    }
private:
    std::vector<sf::RectangleShape> lines;
    int maxLines;
    int displayableLines;
    float lineWidth;
    sf::Clock clock;
    sf::Vector2f panelPosition;
    sf::Vector2f panelSize;
    float velocity;
    RoundedRectangle panel;
};