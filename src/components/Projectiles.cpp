#include "Projectiles.hpp"

namespace R_TYPE {
    Projectiles::Projectiles(bool _byPlayer):
    Component(Component::Type::PROJECTILES)
    {
        byPlayer = _byPlayer;
    }
    Projectiles::~Projectiles() 
    {

    }
}