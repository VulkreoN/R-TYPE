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
        sf::Vector2f distance = {0, 0};

        for (auto &player : manager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            sf::Vector2f distance2 = {0, 0};

            auto target = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);

            distance2.x = target->getPosition().x - selfPos.getPosition().x;
            distance2.y = target->getPosition().y - selfPos.getPosition().y;
            if (distance2.x + distance2.y < distance.x + distance.y || distance.x == 0)
                distance = distance2;
        }
        if (type == Ennemy::Type::TURRET) {
            if (scripts.turretScript(selfPos)) {
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles("projectiles.png", selfPos, getVelocityTarget(distance), false);
                manager.getCurrentScene().addEntity(shoot);
            }
        } else if (type == Ennemy::Type::JORYDE_ALIEN)
            scripts.jorydeScript();
        
    }

    Velocity Ennemy::getVelocityTarget(sf::Vector2f distance)
    {
        Velocity velo = {0, 0};

        if (distance.x < distance.y && distance.y < 0 && distance.x < 0) {
            velo.setX(-0.1f);
            velo.setY((distance.y * -1) * 100 / (distance.x * -1) * -0.001);
        } else if (distance.y < distance.x && distance.x < 0 && distance.y < 0) {
            velo.setY(-0.1f);
            velo.setX((distance.x * -1) * 100 / (distance.y * -1) * -0.001);
        }

        if ((distance.x * -1) > distance.y && distance.x < 0) {
            velo.setX(-0.1f);
            velo.setY(distance.y * 100 / (distance.x * -1) * 0.001);
        } else if ((distance.y * -1) > distance.x && distance.y) {
            velo.setY(-0.1f);
            velo.setX(distance.x * 100 / (distance.y * -1) * 0.001);
        }

        if (distance.x > distance.y && distance.y > 0) {
            velo.setX(0.1f);
            velo.setY(distance.y * 100 / distance.x * 0.001);
        } else if (distance.y > distance.x && distance.x > 0) {
            velo.setY(0.1f);
            velo.setX(distance.x * 100 / distance.y * 0.001);
        }
        return (velo);
    }

    Ennemy::~Ennemy()
    {

    }
}