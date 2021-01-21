#include <SFML/Graphics.hpp>

#include "AssetManager.h"

int main()
{
    AssetManager manager;

    manager.loadTexture("Assets/testing.png", TextureType::GRASS);

    sf::Sprite sprite(manager.getTexture(TextureType::GRASS));


    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;

    return 0;
}
