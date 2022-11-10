#include "Projectiles.hpp"

namespace R_TYPE {
    Projectiles::Projectiles(bool _byPlayer):
    Component(Component::Type::PROJECTILES)
    {
        byPlayer = _byPlayer;
        isActive = true;
        type = Type::BASIC;
        timeSend = 0;
    }

    Projectiles::~Projectiles() 
    {

    }
}