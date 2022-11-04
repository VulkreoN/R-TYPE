#include "Nono.hpp"
#include "Player.hpp"

namespace R_TYPE {
    Nono::Nono():
    Component(Component::Type::NONO)
    {
        upgrade = 0;
        isSnap = false;
        unKillable = true;
    }

    Nono::~Nono()
    {
        upgrade = 0;
    }

    void Nono::nextUpgrade()
    {
        upgrade++;
    }

    sf::Vector2f Nono::getDistance(SceneManager &manager, Position selfPos) 
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

    Velocity Nono::getVelocityTarget(sf::Vector2f distance)
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

        if ((distance.y * -1) < distance.x && distance.y < 0 && distance.x > 0) {
            velo.setY(0.1f);
            velo.setX(-distance.x * 100 / (distance.y * -1) * 0.001);
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

    void Nono::disableNonoPlayer(SceneManager &manager)
    {
        for (auto &e : manager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            if (getPosPlayer() == pos) {
                player->setNono(false);
                player->setLevelNono(0);
            }
        }
    }
}