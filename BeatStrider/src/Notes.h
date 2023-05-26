#pragma once

#include "SFML/Graphics.hpp"

#include "Utils.h"

#include <vector>


enum class NOTE_TYPE
{
    HIGH = 200,
    LOW = 50,
};

class Note
{
public:
    Note(float x, float y, sf::Color color);

    void moveX(float x);
    void Draw(sf::RenderWindow& window);

private:
    int mx, my;
    float radius = 10.0f;
    sf::CircleShape circle;
};


class Line
{
public:
    Line(float x, float y, sf::Color color, const sf::Vector2f& panelPosition, float panelHeight);

    sf::Vector2f GetPosition();

    void AddNote(NOTE_TYPE);

    void Update(float velocity, const sf::Time& delta);
    void Draw(sf::RenderWindow& window);

private:
    static constexpr float lineWidth = 5.f;
    sf::RectangleShape rectangle;
    std::vector<Note> notes;
    sf::Vector2f panelPosition;
};


class Notes 
{
public:
    Notes(const std::string& filePath, int displayableLines, float lineWidth, const sf::Vector2f& panelPosition, const sf::Vector2f& panelSize, float velocity);

    void Update(const sf::Time& delta);
    void Draw(sf::RenderWindow& window);

private:
    std::vector<Line> lines;
    float lineWidth;

    int maxLines;
    int displayableLines;

    RoundedRectangle panel;
    sf::Vector2f panelPosition;
    sf::Vector2f panelSize;

    float velocity;
};