#include "Bonus.hpp"

namespace R_TYPE {
    Bonus::Bonus(Type type):
    Component(IComponent::Type::BONUS)
    {
        type = type;
    }

    Bonus::~Bonus()
    {
    }
}