#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace R_TYPE {
    class Sprite : public Component {
        public: 
            /// @brief Init Sprite class
            /// @param pathTexture Path to the texture file
            Sprite(std::string pathTexture);
            ~Sprite();

            /// @brief Getter sprite
            sf::Sprite getSprite();
        private:
            sf::Sprite sprite;
            sf::Texture texture;
    };
}

#endif