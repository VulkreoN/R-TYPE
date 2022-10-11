#include "Ennemy.hpp"
#include <iostream>

namespace R_TYPE {

    Ennemy::Ennemy(Ennemy::Type _type):
    Component(Component::Type::ENNEMY)
    {
        isAlive = true;
        type = _type;
    }

    void Ennemy::launchScript()
    {
        if (type == Ennemy::Type::TURRET)
            scripts.turretScript();
        else if (type == Ennemy::Type::JORYDE_ALIEN)
            scripts.jorydeScript();
        
    }

    Ennemy::~Ennemy()
    {

    }
}