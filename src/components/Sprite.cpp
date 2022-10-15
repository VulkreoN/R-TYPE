#include "Sprite.hpp"
#include <iostream>

namespace R_TYPE {
    Sprite::Sprite(std::string pathTexture, Position position, sf::IntRect rect):
    Component(Component::Type::SPRITE)
    {
        sf::Vector2f pos(position.getPosition());

        if (!texture.loadFromFile(pathTexture))
            std::cerr << "error load texture path\n";
        sprite.setTexture(texture);
        if (rect.height != 0 && rect.width != 0)
            sprite.setTextureRect(rect);
        sprite.setPosition(pos);
        size = sprite.getTexture()->getSize();
    }

    Sprite::~Sprite()
    {

    }

    sf::Sprite &Sprite::getSprite()
    {
        return(sprite);
    }

    void Sprite::setRect(sf::IntRect rect)
    {
        sprite.setTextureRect(rect);
    }

    void Sprite::setPos(sf::Vector2f pos)
    {
        sprite.setPosition(pos);
    }
}