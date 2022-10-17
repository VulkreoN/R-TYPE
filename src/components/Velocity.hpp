#ifndef VELOCITY_HPP
#define VELOCITY_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace R_TYPE {
    class Velocity : public Component {
    public:
        Velocity(float _x, float _y);
        Velocity(const Velocity &other);
        Velocity(sf::Vector2f _velocity);
        ~Velocity();

        /// @brief get the Velocity 
        sf::Vector2f getVelocity() {return (velocity);};

        void setX(float _x) {velocity.x = _x;};

        void setY(float _y) {velocity.y = _y;};

        void operator=(const Velocity &other);
    private:
        sf::Vector2f velocity;
    };
}

#endif