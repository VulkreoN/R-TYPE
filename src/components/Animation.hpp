/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "Position.hpp"

namespace R_TYPE {
    class Animation : public Component {
        public:
            enum class State {
                NONE = -1,
                IDLE,
                MOVE,
                TRACK,
                SHOOT,
                UP_PRESS,
                UP_DOWN,
                DOWN_DOWN,
                DOWN_PRESS,
                LEFT,
                RIGHT,
            };
            /// @brief Init Animation class
            /// @param id identifier of the entity
            /// @param state State of the Animation
            /// @param rect Rectangle of the texture
            Animation(State state, sf::IntRect rect, int y, int x, int xMax, bool doAction);
            ~Animation();

            /// @brief Getter Animation
            R_TYPE::Animation &getAnimation();

            /// @brief Setter rectangle of the texture
            void setRect(sf::IntRect rect);

            void setState(State state);

            void setY(int y);

            void setX(int x);

            void setXmax(int xMax);

            void setDoActions(bool doActions);

            sf::IntRect getRect();

            State getState();

            int getY();

            int getX();

            int getXmax();

            bool getDoActions();
        private:
            State _state;
            sf::IntRect _rect;
            int _y;
            int _x;
            int _xMax;
            bool _doActions;
    };
}

#endif /* !ANIMATION_HPP_ */
