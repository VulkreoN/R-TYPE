/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GameSystem
*/

#ifndef GAMESYSTEM_HPP_
#define GAMESYSTEM_HPP_

#include "SceneManager.hpp"
#include "ISystem.hpp"
#include "IScene.hpp"
#include "Entity.hpp"
#include "Ennemy.hpp"
#include <SFML/System.hpp>
#include "Velocity.hpp"

namespace R_TYPE {

    class GameSystem: public ISystem {
        public:
            GameSystem();
            ~GameSystem();

            void init(SceneManager &sceneManager) final;
            void update(SceneManager &sceneManager, uint64_t deltaTime) final;
            void destroy() final;

            static std::shared_ptr<Entity> createProjectiles(std::string path, Position pos, Velocity velocity, bool byPlayer);
        protected:

            std::shared_ptr<Entity> createSprite(std::string path, int posX, int posY);
            std::shared_ptr<Entity> createPlayer(int posX, int posY);
            std::shared_ptr<Entity> createText(std::string text, int posX, int posY, int size);
            std::shared_ptr<Entity> createEnnemy(std::string path, int posX, int posY, float angle, Ennemy::Type type);
            void createButtonEvent(std::shared_ptr<Entity> &entity, SceneManager::SceneType goTo, sf::Vector2i click);
            std::shared_ptr<Entity> createCamera(int posX, int posY, int rectX, int rectY);

            std::unique_ptr<R_TYPE::IScene> createSceneTest();
            std::unique_ptr<R_TYPE::IScene> createMainMenu();
            std::unique_ptr<R_TYPE::IScene> createOptionMenu();
            std::unique_ptr<R_TYPE::IScene> createPauseMenu();
            std::unique_ptr<R_TYPE::IScene> createFirstLevel();
        private:
    };
}

#endif /* !GAMESYSTEM_HPP_ */
