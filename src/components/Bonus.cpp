#include "Bonus.hpp"

namespace R_TYPE {
    Bonus::Bonus(BonusType type):
    Component(IComponent::Type::BONUS)
    {
        type = type;
    }

    Bonus::~Bonus()
    {
    }
}