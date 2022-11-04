/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include "Sprite.hpp"
    #include "Velocity.hpp"
    #include "Bonus.hpp"

namespace R_TYPE {
    class Player : public Component {
        public:
            /// @brief Init Player class
            /// @param position Position of the player
            Player(Position position);
            ~Player();

            /// @brief Set the position of the player
            /// @param pos Position of the player
            void setPosition(sf::Vector2f pos);

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

            /// @brief Add a bonus to the player
            /// @param _bonus Bonus to add
            void addBonus(Bonus::BonusType bonus);

            /// @brief if the player has the bonus
            /// @param bonus Bonus to check
            bool hasBonus(Bonus::BonusType bonus);

            void setBonus(Bonus::BonusType _bonus, bool state) {bonus[_bonus] = state;};

            void setNono(bool nono) {_hasNono = nono;};
            bool getNono() {return _hasNono;};

            sf::Clock clock;
            sf::Time chargedTime;
        private:
            int8_t _id;
            std::unique_ptr<Sprite> _spritesheet;
            std::map<Bonus::BonusType, bool> bonus;
            Position _pos;
            bool _attacking;
            bool _alive;
            bool _hasNono;
    };
}

#endif /* !PLAYER_HPP_ */
