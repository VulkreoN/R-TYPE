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
            Sprite(std::string pathTexture, Position position, sf::IntRect rect = sf::IntRect(0, 0, 0, 0));
            ~Sprite();

            /// @brief Getter sprite
            sf::Sprite &getSprite();

            void setPos(sf::Vector2f pos);

            /// @brief Setter rectangle of the texture
            void setRect(sf::IntRect rect);
        private:
            sf::Sprite sprite;
            sf::Vector2u size;
            sf::Texture texture;
    };
}

#endif