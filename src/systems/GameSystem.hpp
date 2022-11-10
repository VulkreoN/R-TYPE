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
#include "Animation.hpp"

namespace R_TYPE {

    class GameSystem: public ISystem {
        public:
            GameSystem();
            ~GameSystem();

            void init(SceneManager &sceneManager) final;
            void update(SceneManager &sceneManager, uint64_t deltaTime) final;
            void destroy() final;

            static std::shared_ptr<Entity> createBonus(int name, Position pos, Bonus::BonusType type, sf::IntRect rect = sf::IntRect(3, 1, 16, 16));
            void updateClient(SceneManager &sceneManager, uint64_t deltaTime);
            void updateServeur(SceneManager &sceneManager, uint64_t deltaTime);

            static sf::FloatRect getRectWindow() { return rectWindow; };
            static void setNbrBasicShoot(int nbr) { nbrBasicShoot = nbr; };
            static int getNbrBasicShoot() { return nbrBasicShoot; };
            static void setNbrTurretShoot(int nbr) { nbrTurretShoot = nbr; };
            static int getNbrTurretShoot() { return nbrTurretShoot; };
            static void setNbrRocketShoot(int nbr) { nbrRocketShoot = nbr; };
            static int getNbrRocketShoot() { return nbrRocketShoot; };
            static std::shared_ptr<Entity> createPlayer(int id, int name, int posX, int posY);
            static std::shared_ptr<Entity> createProjectiles(int id, int name, Position pos, Velocity velocity, bool byPlayer, sf::IntRect rect = sf::IntRect(0, 0, 0, 0));
        protected:
            std::shared_ptr<Entity> createNono(int name, Position pos);
            std::shared_ptr<Entity> createSprite(int id, int name, int posX, int posY, sf::IntRect rect = sf::IntRect(0, 0, 0, 0));
            std::shared_ptr<Entity> createText(int id, std::string text, int posX, int posY, int size);
            std::shared_ptr<Entity> createEnnemy(int id, int name, int posX, int posY, float angle, Ennemy::Type type, Bonus::BonusType bonusType = Bonus::BonusType::NONE);
            void createButtonEvent(std::shared_ptr<Entity> &entity, SceneManager::SceneType goTo, sf::Vector2i click);
            std::shared_ptr<Entity> createCamera(int id, int posX, int posY, int rectX, int rectY);
            std::vector<std::shared_ptr<IEntity>>  createWavesEnnemy(int first_id, int name, int posX, int posY, float angle, Ennemy::Type type);

            std::unique_ptr<R_TYPE::IScene> createSceneTest();
            std::unique_ptr<R_TYPE::IScene> createMainMenu();
            std::unique_ptr<R_TYPE::IScene> createOptionMenu();
            std::unique_ptr<R_TYPE::IScene> createPauseMenu();
            std::unique_ptr<R_TYPE::IScene> createFirstLevel();
            std::unique_ptr<R_TYPE::IScene> createSceneLose();
            std::unique_ptr<R_TYPE::IScene> createSceneWin();

            void updateNono(SceneManager &sceneManager, uint64_t deltaTime);
            void updateRectWindow();
        private:
            static sf::FloatRect rectWindow;
            static int nbrBasicShoot;
            static int nbrTurretShoot;
            static int nbrRocketShoot;
    };
}

#endif /* !GAMESYSTEM_HPP_ */
