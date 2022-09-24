#include "Component.hpp"

namespace R_TYPE {
    Component::Component(const Type &type) : _type(type)
    {
    }

    const Component::Type &Component::getType() const
    {
        return _type;
    }

}