#include "Script.hpp"
#include <iostream>

namespace R_TYPE {

    bool Script::turretScript()
    {
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (CurrentFrame.asSeconds() > 5) {
            std::cout << "Turret shoot dans la direction du joueur " << std::endl;
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
            selfVel->setX(selfVel->getVelocity().x * -1);
            std::cout << "Roquette en cloche" << std::endl;
            clock.restart();
            return (true);
        }
        return (false);
    }
}