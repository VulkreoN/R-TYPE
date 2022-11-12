#include "Projectiles.hpp"
#include "Sprite.hpp"
#include "IEntity.hpp"
#include <cmath>
#include <iostream>
#include "Ennemy.hpp"

namespace R_TYPE {
    Projectiles::Projectiles(bool _byPlayer):
    Component(Component::Type::PROJECTILES)
    {
        byPlayer = _byPlayer;
        isActive = true;
        type = Type::BASIC;
        timeSend = 0;
    }

    Projectiles::~Projectiles() 
    {

    }

    void Projectiles::setSpriteAngle(sf::Vector2f distance, std::shared_ptr<IEntity> entity)
    {
        auto sprite = Component::castComponent<Sprite>((*entity)[IComponent::Type::SPRITE]);
        float angle = atan(distance.y / distance.x) * 180 / 3.14159265;
        Velocity velocity = Ennemy::getVelocityTarget(distance);

        if (velocity.getVelocity().x < 0) {
            if (angle < 0)
                angle = 360 - (90 - angle);
            else
                angle += 270;
        } else {
            if (angle < 0)
                angle = 90 - angle;
            else
                angle += 90;
        }
        sprite->getSprite().setRotation(angle);
    }
}