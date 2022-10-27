#include "Script.hpp"
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

    bool Script::jorydeScript(sf::Vector2f distance, std::shared_ptr<R_TYPE::Velocity> selfVel)
    {
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (distance.x != 0 && distance.y != 0) {
            selfVel->setX((distance.x + 100) * 0.001);
            selfVel->setY(distance.y * 0.001);
        }
        if (CurrentFrame.asSeconds() < 0.5f) {
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

    bool Script::robotScript(sf::Vector2f distance, std::shared_ptr<R_TYPE::Velocity> selfVel)
    {
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (CurrentFrame.asSeconds() > 5) {
            std::cout << "Roquette en cloche" << std::endl;
            clock.restart();
            return (true);
        }
        return (false);
    }

    void Script::spatialScript(std::shared_ptr<R_TYPE::Velocity> selfVel)
    {
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (CurrentFrame.asSeconds() > 0.5f) {
            selfVel->setY(selfVel->getVelocity().y * -1);
            clock.restart();
        }
    }
}