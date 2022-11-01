#include "Velocity.hpp"

namespace R_TYPE {
    Velocity::Velocity(float _x, float _y):
    Component(Component::Type::VELOCITY)
    {
        velocity.x = _x;
        velocity.y = _y;
        _isInitialized = true;
    }

    Velocity::Velocity(const Velocity &other):
    Component(Component::Type::VELOCITY)
    {
        velocity.x = other.velocity.x;
        velocity.y = other.velocity.y;
        _isInitialized = true;
    }

    Velocity::Velocity(sf::Vector2f _velocity):
    Component(Component::Type::VELOCITY)
    {
        velocity = _velocity;
        _isInitialized = true;
    }


    void Velocity::operator=(const Velocity &other)
    {
        velocity.x = other.velocity.x;
        velocity.y = other.velocity.y;
    }

    Velocity::~Velocity()
    {
    }
}