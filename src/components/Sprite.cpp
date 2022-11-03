#include "Sprite.hpp"
#include <iostream>
#include "GraphicSystem.hpp"

namespace R_TYPE {
    Sprite::Sprite(int name, Position position, float angle, sf::IntRect rect):
    Component(Component::Type::SPRITE), name(name), position(position), angle(angle), rect(rect)
    {
        isInit = false;
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