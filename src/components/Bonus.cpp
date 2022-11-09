#include "Bonus.hpp"
#include <iostream>

namespace R_TYPE {
    Bonus::Bonus(BonusType _type):
    Component(IComponent::Type::BONUS)
    {
        type = _type;
    }

    Bonus::~Bonus()
    {
    }

    Bonus::BonusType Bonus::getType()
    {
        return type;
    }
}