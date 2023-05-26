#include "Utils.h"

std::vector<std::vector<int>> ReadTextFile(const std::string& filePath, int& ROWS, int& COLS)
{
    std::vector<std::vector<int>> data;
    std::ifstream inputFile(filePath);

    if (inputFile.is_open())
    {
        std::string line;

        while (std::getline(inputFile, line))
        {
            std::vector<int> row;

            for (char c : line)
            {
                int value = c - '0';
                row.push_back(value);
            }

            data.push_back(row);
        }

        ROWS = data.size();
        COLS = data[0].size();
    }

    else
    {
        std::cerr << "[ERROR]: Failed to open the file: " << filePath << std::endl;
    }

    return data;
}

void WriteTextFile(int ROWS, int COLS, const std::string& filePath, const std::vector<std::vector<int>>& level_matrix) 
{

    std::ofstream outputFile(filePath);

    if (outputFile.is_open())
    {
        for (int i = 0; i < COLS; ++i)
        {
            for (int j = 0; j < ROWS; ++j)
            {
                outputFile << level_matrix[i][j];
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }
    else
    {
        std::cout << "[ERROR]: Unable to create file." << std::endl;
    }
}

std::vector<std::vector<int>> ReadCSVFile(const std::string& filePath, int& ROWS, int& COLS)
{
    std::vector<std::vector<int>> data;
    std::ifstream inputFile(filePath);


    if (inputFile.is_open())
    {
        std::string line;

        while (std::getline(inputFile, line))
        {
            std::vector<int> row;
            std::stringstream ss(line);
            std::string cell;

            while (std::getline(ss, cell, ','))
            {
                cell.erase(std::remove_if(cell.begin(), cell.end(), ::isspace), cell.end());
                row.push_back(std::stoi(cell));
            }

            data.push_back(row);
        }

        ROWS = data.size();
        COLS = data[0].size();

    }
    else
    {
        std::cerr << "[ERROR]: Failed to open the file: " << filePath << std::endl;
    }

    std::cout << "COLS: " << COLS << ", ROWS: " << ROWS << std::endl;

    return data;
}

std::vector<sf::Texture> GetTexturesFromFolder(const std::string& filePath)
{
    std::vector<sf::Texture> textures;

    for (const auto& entry : std::filesystem::directory_iterator(filePath))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().string();
            sf::Texture texture;

            if (texture.loadFromFile(filename))
            {
                textures.push_back(texture);
            }
        }
    }

    return textures;
}

RoundedRectangle::RoundedRectangle(float width, float height, float radius, int points, sf::Vector2f position, sf::Color color)
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

void RoundedRectangle::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
