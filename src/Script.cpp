#include "Script.hpp"
#include "Ennemy.hpp"
#include <iostream>

namespace R_TYPE {

    bool Script::turretScript()
    {
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (CurrentFrame.asSeconds() > 5) {
            clock.restart();
            return (true);
        }
        return (false);
    }

    bool Script::jorydeScript(sf::Vector2f distance, std::shared_ptr<R_TYPE::IEntity> ennemy)
    {
        auto selfVel = Component::castComponent<Velocity>((*ennemy)[IComponent::Type::VELOCITY]);
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (distance.x != 0 && distance.y != 0) {
            selfVel->setX((distance.x + 100) * 0.001);
            if (selfVel->getVelocity().x < 0) {
                auto comp_e = (*ennemy)[IComponent::Type::ENNEMY];
                auto ennemy = Component::castComponent<Ennemy>(comp_e);
                ennemy->setState(Animation::State::RIGHT);
            } else if (selfVel->getVelocity().x >= 0) {
                auto comp_p = (*ennemy)[IComponent::Type::ENNEMY];
                auto ennemy = Component::castComponent<Ennemy>(comp_p);
                ennemy->setState(Animation::State::LEFT);
            }
            selfVel->setY(distance.y * 0.001);
        }
        if (CurrentFrame.asSeconds() < 0.5f) {
            auto comp_p = (*ennemy)[IComponent::Type::ENNEMY];
            auto ennemy = Component::castComponent<Ennemy>(comp_p);
            ennemy->setState(Animation::State::IDLE);
            selfVel->setX(0);
            selfVel->setY(0);
        }

        if (CurrentFrame.asSeconds() > 2) {
            std::cout << "Laser tout droit " << std::endl;
            clock.restart();
            return (true);
        }
        return (false);
    }

    bool Script::robotScript(sf::Vector2f distance, std::shared_ptr<R_TYPE::IEntity> ennemy)
    {
        auto selfVel = Component::castComponent<Velocity>((*ennemy)[IComponent::Type::VELOCITY]);
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (repeat == 5) {
            repeat = 0;
            if (selfVel->getVelocity().x == 0)
                selfVel->setX(-0.03f);
        }
        if (CurrentFrame.asMilliseconds() > 375 && repeat > 0) {
            repeat += 1;
            clock.restart();
            return(true);
        }

        if (CurrentFrame.asSeconds() > 5 && repeat == 0) {
            std::cout << "5 Roquettes" << std::endl;
            selfVel->setX(0);
            repeat = 1;
            clock.restart();
            return (true);
        }
        return (false);
    }

    void Script::spatialScript(std::shared_ptr<R_TYPE::IEntity> ennemy)
    {
        auto selfVel = Component::castComponent<Velocity>((*ennemy)[IComponent::Type::VELOCITY]);
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (CurrentFrame.asSeconds() > 0.5f) {
            selfVel->setY(selfVel->getVelocity().y * -1);
            clock.restart();
        }
    }
}