#include "Ennemy.hpp"
#include <iostream>

namespace R_TYPE {

    Ennemy::Ennemy():
    Component(Component::Type::ENNEMY)
    {
        isAlive = true;
        type = Ennemy::Type::TURRET;
    }

    void Ennemy::script1()
    {
        sf::Time elapsed1 = clock.getElapsedTime();

        if (elapsed1.asSeconds() > 2) {
            std::cout << "Turret shoot" << std::endl;
            clock.restart();
        }
    }

    void Ennemy::launchScript()
    {
        if (type == Ennemy::Type::TURRET)
            script1();
    }

    Ennemy::~Ennemy()
    {

    }
}