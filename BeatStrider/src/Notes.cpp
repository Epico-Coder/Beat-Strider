#include "Notes.h"

Note::Note(float x, float y, sf::Color color)
    : mx(x), my(y), circle(radius)
{
    circle.setPosition(x - radius, y);
    circle.setFillColor(color);
}

void Note::moveX(float x)
{
    mx += x;
    circle.move(x, 0);
}

void Note::Draw(sf::RenderWindow& window)
{
    window.draw(circle);
}

Line::Line(float x, float y, sf::Color color, const sf::Vector2f& panelPosition, float panelHeight)
    : rectangle(sf::Vector2f(lineWidth, panelHeight)), panelPosition(panelPosition)
{
    rectangle.setPosition(x, y);
    rectangle.setOrigin(lineWidth / 2, 0);
    rectangle.setFillColor(color);
}

void Line::AddNote(NOTE_TYPE note_type)
{
    Note note(rectangle.getPosition().x, rectangle.getPosition().y + rectangle.getSize().y - static_cast<float>(note_type), sf::Color{236u, 203u, 20u, 200u});
    notes.push_back(note);
}

void Line::Update(float velocity, const sf::Time& delta)
{
    float x_offset = velocity * delta.asMilliseconds();

    for (auto& note : notes)
    {
        note.moveX(x_offset);
    }

    rectangle.setPosition(rectangle.getPosition().x + x_offset, rectangle.getPosition().y);
}

void Line::Draw(sf::RenderWindow& window)
{
    window.draw(rectangle);

    for (auto& note : notes)
    {
        note.Draw(window);
    }
}

sf::Vector2f Line::GetPosition()
{
    return rectangle.getPosition();
}

Notes::Notes(const std::string& filePath, int displayableLines, float lineWidth, const sf::Vector2f& panelPosition, const sf::Vector2f& panelSize, float velocity)

    : displayableLines(displayableLines), lineWidth(lineWidth), panelPosition(panelPosition), panelSize(panelSize), velocity(velocity),
    panel(panelSize.x, panelSize.y, 10, 10, panelPosition, sf::Color(31u, 37u, 42u, 255u))
{
    int temp;
    auto line_map = ReadCSVFile(filePath, maxLines, temp);

    for (int i = 0; i < maxLines; i++)
    {
        Line line(panelPosition.x - (i * panelSize.x / displayableLines), panelPosition.y, sf::Color(175u + i * 3, 90u + i * 3, 90u + i * 3, 175u), panelPosition, panelSize.y);

        for (int j = 0; j < line_map[i].size(); j++)
        {
            switch (line_map[i][j])
            {
            case 0:
                line.AddNote(NOTE_TYPE::HIGH);
                break;
            case 1:
                line.AddNote(NOTE_TYPE::LOW);
                break;
            default:
                //line.AddNote(0);
                break;
            } 
        }

        lines.push_back(line);
    }
}

void Notes::Update(const sf::Time& delta)
{
    for (int i = 0; i < maxLines; i++)
    {
        lines[i].Update(velocity, delta);
    }
}

void Notes::Draw(sf::RenderWindow& window)
{
    panel.Draw(window);

    for (int i = 0; i < maxLines; i++)
    {
        if ((lines[i].GetPosition().x > panelPosition.x) && (lines[i].GetPosition().x < panelPosition.x + panelSize.x))
        {
            lines[i].Draw(window);
        }
    }
}