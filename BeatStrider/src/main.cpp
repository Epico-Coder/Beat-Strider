#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Orbs.h"
#include "Utils.h"
#include "AudioHandler.h"
#include "Notes.h"

#include <unordered_map>
#include <iostream>

int main() 
{
    Seed();

    const int WIDTH = 1600;
    const int HEIGHT = 900;

    const int TEXTURE_SIZE = 8;

    int LEVEL_ROWS;
    int LEVEL_COLS;

    // Creating window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Beat Stride");
    window.setFramerateLimit(0);

    // Setting level
    auto level = ReadCSVFile("levels/level.csv", LEVEL_ROWS, LEVEL_COLS);

    std::unordered_map<int, std::string> level_map
    {
        {0  , "resources/Tiles/0.png"  },
        {1  , "resources/Tiles/1.png"  },
        {2  , "resources/Tiles/2.png"  },
        {3  , "resources/Tiles/3.png"  },
        {4  , "resources/Tiles/4.png"  },
        {5  , "resources/Tiles/5.png"  },
        {6  , "resources/Tiles/6.png"  },
        {7  , "resources/Tiles/7.png"  },
        {8  , "resources/Tiles/8.png"  },
        {9  , "resources/Tiles/9.png"  },
        {10 , "resources/Tiles/10.png" },
        {11 , "resources/Tiles/11.png" },
        {12 , "resources/Tiles/12.png" },
        {13 , "resources/Tiles/13.png" },
        {14 , "resources/Tiles/14.png" },
        {15 , "resources/Tiles/15.png" },
    };

    // Setting textures
    std::unordered_map<int, sf::Texture> textures;
    for (auto& pair : level_map) 
    {
        sf::Texture texture;
        if (!texture.loadFromFile(pair.second)) 
        {
            return EXIT_FAILURE;
        }
        textures[pair.first] = texture;
    }
    
    // Notes
    Notes notes(50, 50, 1.0f, sf::Vector2f(200, (HEIGHT - HEIGHT / 4.0f) - 10), sf::Vector2f(WIDTH - 400, HEIGHT / 4.0f), 100.0f);

    // Player
    Player player("resources/Heroes/Knight/Idle/Idle-Sheet.png", "resources/Heroes/Knight/Run/Run-Sheet.png");

    // Gif bg
    auto frames = GetTexturesFromFolder("resources/backgrounds/tunnelspin");
    AnimationByTextures background_anim(frames, 0.1f);

    sf::RectangleShape rectangle(sf::Vector2f(WIDTH, HEIGHT)); 
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(0, 0);

    // Audio
    Audio theme("resources/music/moonlight.ogg");
    theme.play();

    // Orbs
    auto orbs = CreateOrbsRandomly(20);

    sf::Clock clock_restart;
    sf::Clock clock_forever;
    
    while (window.isOpen()) 
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time delta = clock_restart.restart();

        background_anim.Update();
        rectangle.setTexture(&background_anim.GetTexture());

        player.Update(delta, clock_forever.getElapsedTime());

        notes.Update();

        // Draw the level
        for (int i = 0; i < LEVEL_ROWS; i++) {
            for (int j = 0; j < LEVEL_COLS; j++) {

                sf::Sprite sprite;

                int id = level[i][j];
                
                sprite.setScale(WIDTH / LEVEL_COLS / TEXTURE_SIZE, HEIGHT / LEVEL_ROWS / TEXTURE_SIZE);
                sprite.setPosition(j * WIDTH / LEVEL_COLS, i * HEIGHT / LEVEL_ROWS);
                sprite.setTexture(textures[id]);

                window.draw(sprite);
            }
        }

        // Draw background gif
        window.draw(rectangle);

        player.Draw(window);

        DrawOrbsRandomly(orbs, player, window);

        notes.Draw(window);

        window.display();
    }

    return EXIT_SUCCESS;
}
