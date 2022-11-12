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
            selfVel->setX((distance.x + 75) * 0.001);
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

        if (repeat == 3) {
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
            selfVel->setX(0);
            std::cout << "3 Roquettes" << std::endl;
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
            if (selfVel->getVelocity().x == 0) {
                selfVel->setX(-0.05f);
                selfVel->setY(0.05f);
            }
            selfVel->setY(selfVel->getVelocity().y * -1);
            clock.restart();
        }
    }

    void Script::bossScript(std::shared_ptr<R_TYPE::IEntity> ennemy)
    {
        CurrentFrame = clock.getElapsedTime();
        auto comp_p = (*ennemy)[IComponent::Type::ENNEMY];
        auto boss = Component::castComponent<Ennemy>(comp_p);

        if (CurrentFrame.asSeconds() > 7) {
            boss->setState(Animation::State::BORN1);
        }
        if (CurrentFrame.asSeconds() > 8) {
            boss->setState(Animation::State::BORN2);
        }
        if (CurrentFrame.asSeconds() > 9) {
            boss->setState(Animation::State::BORN3);
        }
        if (CurrentFrame.asSeconds() > 10) {
            boss->setState(Animation::State::BORN4);
        }
        if (CurrentFrame.asSeconds() > 11) {
            boss->setState(Animation::State::BORN5);
        }
        if (CurrentFrame.asSeconds() > 12) {
            boss->setState(Animation::State::BORN6);
        }
        if (CurrentFrame.asSeconds() > 13) {
            boss->setState(Animation::State::BORN7);
        }
        if (CurrentFrame.asSeconds() > 14) {
            boss->setState(Animation::State::BORN8);
        }
    }
}