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

            /// @brief Draw sprite in the window
            /// @param window the window of the game
            void drawSprite(sf::RenderWindow window);
        private:
            sf::Sprite sprite;
    };
}

#endif