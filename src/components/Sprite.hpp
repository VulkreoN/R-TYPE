#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include "Position.hpp"

namespace R_TYPE {
    class Sprite : public Component {
        public:
            /// @brief Init Sprite class
            /// @param pathTexture Path to the texture file
            /// @param position Position of the sprite
            /// @param rect Rectangle of the texture
            Sprite(int name, Position position, float angle = 0, sf::IntRect rect = sf::IntRect(0, 0, 0, 0));
            ~Sprite();

            /// @brief Getter sprite
            sf::Sprite &getSprite();

            void setPos(sf::Vector2f pos);

            /// @brief Setter rectangle of the texture
            void setRect(sf::IntRect rect);

            void setAngle(float angle);

            int getName() const {return (name);};
            Position getPosition() const {return (position);};
            float getAngle() const {return (angle);};
            sf::IntRect getRect() const {return (rect);};

            bool isInit;
        private:
            sf::Sprite sprite;
            sf::Vector2u size;
            int name;
            Position position;
            float angle;
            sf::IntRect rect;
    };
}

#endif