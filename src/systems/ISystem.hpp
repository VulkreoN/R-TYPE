/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include <iostream>
#include <memory>

namespace R_TYPE {

    class SceneManager;

    class ISystem {
        public:

            /**
             * @brief Initialize the system before the game loop
             * @param manager The scene manager
             */
            virtual void init(SceneManager &manager) = 0;

            /**
             * @brief Update the system called every time deltaTime >= UPDATE_DELTA
             * @param manager The scene manager
             * @param deltaTime The time since the last update
             */
            virtual void update(SceneManager &manager, uint64_t deltaTime) = 0;

            /**
             * @brief Destroy the system at the end of the game loop
             */
            virtual void destroy() = 0;
    };
}

#endif /* !ISYSTEM_HPP_ */
