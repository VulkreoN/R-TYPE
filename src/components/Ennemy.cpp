#include "Ennemy.hpp"
#include <iostream>
#include <cmath>
#include "Entity.hpp"
#include "GameSystem.hpp"

namespace R_TYPE {

    Ennemy::Ennemy(Ennemy::Type _type):
    Component(Component::Type::ENNEMY)
    {
        isAlive = true;
        type = _type;
    }

    void Ennemy::launchScript(SceneManager &manager, Position selfPos)
    {
        sf::Vector2i targetPos;
        int distance = 0;

        // changer le sprite_2D avec le player
        for (auto &player : manager.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            int distance2 = 0;
            auto target = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);

            distance2 = (target->getPosition().x - selfPos.getPosition().x) * (target->getPosition().x - selfPos.getPosition().x);
            distance2 += (target->getPosition().y - selfPos.getPosition().y) * (target->getPosition().y - selfPos.getPosition().y);
            if (sqrt(distance2) < distance && sqrt(distance2) > 0 || distance == 0)
                distance = sqrt(distance2);
        }
        if (type == Ennemy::Type::TURRET) {
            if (scripts.turretScript(distance, selfPos)) {
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles("projectiles.png", selfPos.getPosition().x, selfPos.getPosition().y);
                manager.getCurrentScene().addEntity(shoot);
            }
        } else if (type == Ennemy::Type::JORYDE_ALIEN)
            scripts.jorydeScript();
        
    }

    Ennemy::~Ennemy()
    {

    }
}