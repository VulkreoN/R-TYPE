#include "Sprite.hpp"
#include <iostream>

namespace R_TYPE {
    Sprite::Sprite(std::string pathTexture):
    Component(Component::Type::SPRITE)
    {
        sf::Texture texture;

        if (!texture.loadFromFile(pathTexture))
            std::cerr << "error load texture path\n";
        sprite.setTexture(texture);
    }

    void Sprite::drawSprite(sf::RenderWindow window)
    {
        window.draw(sprite);
    }

    Sprite::~Sprite() 
    {

    }
}