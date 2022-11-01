#include "Sprite.hpp"
#include <iostream>
#include "GraphicSystem.hpp"

namespace R_TYPE {
    Sprite::Sprite(int name, Position position, float angle, sf::IntRect rect):
    Component(Component::Type::SPRITE)
    {
        sf::Vector2f pos(position.getPosition());

        sprite.setTexture(GraphicSystem::getTextures()[name-1]);
        if (rect.height != 0 && rect.width != 0)
            sprite.setTextureRect(rect);
        sprite.setPosition(pos);
        sprite.setRotation(angle);
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

    void Sprite::setAngle(float angle)
    {
        sprite.setRotation(angle);
    }
}