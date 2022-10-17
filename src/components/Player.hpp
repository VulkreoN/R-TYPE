/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "Sprite.hpp"

namespace R_TYPE {
    class Player : public Component {
        public:
            /// @brief Init Player class
            /// @param position Position of the player
            /// @param id Id of the player 1 to 4
            Player(Position position, int8_t id = 1);
            ~Player();

            /// @brief Set the position of the player
            /// @param position Position of the player
            void setPosition(sf::Vector2f _pos);

            /// @brief Get the position of the player
            sf::Vector2f getPosition();

            /// @brief Get the sprite of the player
            sf::Sprite &getSprite() const;

            /// @brief Return the player's life state
            bool isAlive() const;

            /// @brief Return the player's attack state
            bool isAttacking() const;

            /// @brief Set the player's life state
            /// @param alive State
            void setAlive(bool alive);

            /// @brief Set the player's attack state
            /// @param attacking State
            void setAttacking(bool attacking);

        private:
            int8_t _id;
            std::unique_ptr<Sprite> _spritesheet;
            Position _pos;
            bool _attacking;
            bool _alive;
    };
}

#endif /* !PLAYER_HPP_ */
