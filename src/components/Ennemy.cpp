#include "Ennemy.hpp"
#include <iostream>
#include <cmath>
#include "Entity.hpp"
#include "GameSystem.hpp"
#include "Player.hpp"

namespace R_TYPE {

    Ennemy::Ennemy(Ennemy::Type _type):
    Component(Component::Type::ENNEMY)
    {
        isAlive = true;
        type = _type;
        isLooting = Bonus::BonusType::NONE;
    }

    void Ennemy::launchScript(SceneManager &manager, std::shared_ptr<R_TYPE::IEntity> ennemy)
    {
        auto selfPos = Component::castComponent<Position>((*ennemy)[IComponent::Type::POSITION]);
        auto selfVel = Component::castComponent<Velocity>((*ennemy)[IComponent::Type::VELOCITY]);
        sf::Vector2f distance = getDistance(manager, *selfPos);

        if (type == Ennemy::Type::TURRET) {
            if (scripts.turretScript()) {
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles(54, *selfPos, getVelocityTarget(distance), false);
                manager.getCurrentScene().addEntity(shoot);
            }
        } else if (type == Ennemy::Type::JORYDE_ALIEN) {
            if (scripts.jorydeScript(distance, selfVel)) {
                if (distance.x > 0)
                    isAlive = false;
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles(9, *selfPos, Velocity(-0.1f, 0), false, sf::IntRect(18, 59, 15, 15));
                manager.getCurrentScene().addEntity(shoot);
            }
        } else if (type == Ennemy::Type::ROBOT_DINO) {
            if (scripts.robotScript(distance, selfVel)) {
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles(10, *selfPos, Velocity(0, -0.1f), false, sf::IntRect(191, 63, 6, 12));
                manager.getCurrentScene().addEntity(shoot);
            }
        } else if (type == Ennemy::Type::SPATIAL) {
            scripts.spatialScript(selfVel);
        }
    }

    sf::Vector2f Ennemy::getDistance(SceneManager &manager, Position selfPos) 
    {
        sf::Vector2i targetPos;
        sf::Vector2f distance = {0, 0};

        for (auto &player : manager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            sf::Vector2f distance2 = {0, 0};

            auto target = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);

            distance2.x = target->getPosition().x + 15 - selfPos.getPosition().x;
            distance2.y = target->getPosition().y + 6 - selfPos.getPosition().y;
            if (distance2.x + distance2.y < distance.x + distance.y || distance.x == 0)
                distance = distance2;
        }
        return (distance);
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
        } else if ((distance.y * -1) < distance.x && distance.y > 0 && distance.x < 0) {
            velo.setY(0.1f);
            velo.setX(-distance.x * 100 / (distance.y * -1) * 0.001);
        }

        if (distance.x > distance.y) {
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