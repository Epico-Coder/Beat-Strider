#pragma once
	
#include "SFML/Graphics.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

std::vector<std::vector<int>> ReadTextFile(const std::string& filePath, int& ROWS, int& COLS);
void WriteTextFile(int ROWS, int COLS, const std::string& filePath, const std::vector<std::vector<int>>& level_matrix);

std::vector<std::vector<int>> ReadCSVFile(const std::string& filePath, int& ROWS, int& COLS);

std::vector<sf::Texture> GetTexturesFromFolder(const std::string& filePath);

class RoundedRectangle
{
public:
    RoundedRectangle(float width, float height, float radius, int points, sf::Vector2f position, sf::Color color);
    
    void Draw(sf::RenderWindow& window);

private:
    sf::ConvexShape shape;

};