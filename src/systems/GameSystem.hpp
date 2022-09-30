/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GameSystem
*/

#ifndef GAMESYSTEM_HPP_
#define GAMESYSTEM_HPP_

#include "ISystem.hpp"
#include "IScene.hpp"

namespace R_TYPE {

    class GameSystem: public ISystem {
        public:
            GameSystem();
            ~GameSystem();

            void init(SceneManager &sceneManager) final;
            void update(SceneManager &sceneManager, uint64_t deltaTime) final;
            void destroy() final;

        protected:

            std::unique_ptr<R_TYPE::IScene> createSceneTest();
        private:
    };
}

#endif /* !GAMESYSTEM_HPP_ */
