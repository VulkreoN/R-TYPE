/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GameSystem
*/

#ifndef GAMESYSTEM_HPP_
#define GAMESYSTEM_HPP_

#include "ISystem.hpp"

namespace R_TYPE {
    class GameSystem: public ISystem {
        public:
            GameSystem();
            ~GameSystem();

            void init(SceneManager &manager) final;
            void update(SceneManager &manager, uint64_t deltaTime) final;
            void destroy() final;

        protected:
        private:
    };
}

#endif /* !GAMESYSTEM_HPP_ */
