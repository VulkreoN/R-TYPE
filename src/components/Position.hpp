#ifndef POSITION_HPP
#define POSITION_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace R_TYPE {
    class Position : public Component {
    public:
        Position(float _x, float _y);
        Position(const Position &other);
        Position(sf::Vector2f _pos);
        ~Position();

        /// @brief get the position 
        sf::Vector2f getPosition() {return (pos);};

        void operator=(const Position &other);
    private:
        sf::Vector2f pos;
    };
}

#endif