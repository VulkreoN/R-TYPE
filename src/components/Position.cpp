#include "Position.hpp"

namespace R_TYPE {
    Position::Position(float _x, float _y):
    Component(Component::Type::POSITION)
    {
        pos.x = _x;
        pos.y = _y;
        _isInitialized = true;
    }

    Position::Position(const Position &other):
    Component(Component::Type::POSITION)
    {
        pos.x = other.pos.x;
        pos.y = other.pos.y;
        _isInitialized = true;
    }

    Position::Position(sf::Vector2f _pos):
    Component(Component::Type::POSITION)
    {
        pos = _pos;
        _isInitialized = true;
    }

    void Position::operator=(const Position &other)
    {
        pos.x = other.pos.x;
        pos.y = other.pos.y;
    }

    Position::~Position()
    {
    }
}
