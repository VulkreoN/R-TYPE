#include "Sprite.hpp"
#include <iostream>

namespace R_TYPE {
    Sprite::Sprite(std::string pathTexture, Position position):
    Component(Component::Type::SPRITE)
    {
        sf::Vector2f pos(position.getPosition());

        if (!texture.loadFromFile(pathTexture))
            std::cerr << "error load texture path\n";
        sprite.setTexture(texture);
        sprite.setPosition(pos);
    }

    sf::Sprite Sprite::getSprite()
    {
        return(sprite);
    }

    Sprite::~Sprite() 
    {

    }

    void Sprite::setPos(sf::Vector2f pos)
    {
        sprite.setPosition(pos);
    }
}