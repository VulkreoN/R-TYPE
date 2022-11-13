#include "Ennemy.hpp"
#include <iostream>
#include <cmath>
#include "Entity.hpp"
#include "GameSystem.hpp"
#include "Player.hpp"
#include <cmath>

#define PI 3.14159265

namespace R_TYPE {

    Ennemy::Ennemy(Ennemy::Type _type):
    Component(Component::Type::ENNEMY)
    {
        alive = true;
        dying = false;
        type = _type;
        isLooting = Bonus::BonusType::NONE;
        _pv = 1;
    }

    void Ennemy::launchScript(SceneManager &manager, std::shared_ptr<R_TYPE::IEntity> ennemy, float leftCamera)
    {
        auto selfPos = Component::castComponent<Position>((*ennemy)[IComponent::Type::POSITION]);
        auto selfVel = Component::castComponent<Velocity>((*ennemy)[IComponent::Type::VELOCITY]);
        sf::Vector2f distance = getDistance(manager, *selfPos);

        if (dying)
            return;
        if (type == Ennemy::Type::TURRET) {
            updateAngle(distance, ennemy);
            if (scripts.turretScript()) {
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles(6021 + GameSystem::getNbrTurretShoot(), 54, 
                *selfPos, getVelocityTarget(distance), false, sf::IntRect(0, 0, 14, 12));
                GameSystem::setNbrTurretShoot(GameSystem::getNbrTurretShoot() + 1);
                manager.getCurrentScene().addEntity(shoot);
            }
        } else if (type == Ennemy::Type::JORYDE_ALIEN) {
            if (scripts.jorydeScript(distance, ennemy)) {
                if (distance.x > 0)
                    alive = false;
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles(6020, 9, *selfPos, Velocity(-0.1f, 0), false, sf::IntRect(18, 59, 15, 15));
                manager.getCurrentScene().addEntity(shoot);
            }
        } else if (type == Ennemy::Type::ROBOT_DINO) {
            if (scripts.robotScript(distance, ennemy)) {
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles(6030 + GameSystem::getNbrRocketShoot(), 10, 
                *selfPos, Velocity(0, -0.1f), false, sf::IntRect(191, 63, 6, 12));
                GameSystem::setNbrRocketShoot(GameSystem::getNbrRocketShoot() + 1);
                manager.getCurrentScene().addEntity(shoot);
            }
        } else if (type == Ennemy::Type::SPATIAL) {
            scripts.spatialScript(ennemy);
        } else if (type == Ennemy::Type::BOSS) {
            if (scripts.bossScript(ennemy, leftCamera)) {
                std::shared_ptr<Entity> shoot = GameSystem::createProjectiles(6066 + GameSystem::getNbrBossShoot(), 30, 
                Position(2070, 120), Velocity(-0.1f, 0), false, sf::IntRect(574, 2062, 24, 22));
                GameSystem::setNbrBossShoot(GameSystem::getNbrBossShoot() + 1);
                manager.getCurrentScene().addEntity(shoot);
            }
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

    void Ennemy::setState(Animation::State state)
    {
        _state = state;
    }

    Animation::State Ennemy::getState()
    {
        return _state;
    }

    void Ennemy::updateAngle(sf::Vector2f distance, std::shared_ptr<R_TYPE::IEntity> ennemy)
    {
        auto sprite = Component::castComponent<Sprite>((*ennemy)[IComponent::Type::SPRITE]);
        angle = distance.x / distance.y;
        angle = atan(angle) * 180 / PI;
        int angleOfSprite = sprite->getAngle();

        if (angle > -90 && angle < -54)
            sprite->setRect(sf::IntRect(87, 2, 15, 14));
        else if (angle > -54 && angle < -18)
            sprite->setRect(sf::IntRect(70, 2, 15, 14));
        else if (angle > -18 && angle < 18)
            sprite->setRect(sf::IntRect(36, 2, 15, 14));
        else if (angle > 18 && angle < 54)
            sprite->setRect(sf::IntRect(19, 2, 15, 14));
        else if (angle > 54 && angle < 90)
            sprite->setRect(sf::IntRect(1, 2, 15, 14));
    }

    void Ennemy::setPv(int pv)
    {
        _pv = pv;
    }

    int Ennemy::getPv()
    {
        return (_pv);
    }
}
