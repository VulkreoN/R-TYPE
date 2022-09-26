#include "Sprite.hpp"
#include <iostream>

namespace R_TYPE {
    Sprite::Sprite(std::string pathTexture):
    Component(Component::Type::SPRITE)
    {
        if (!texture.loadFromFile(pathTexture))
            std::cerr << "error load texture path\n";
        sprite.setTexture(texture);
    }

    sf::Sprite Sprite::getSprite()
    {
        return(sprite);
    }

    Sprite::~Sprite() 
    {

    }
}