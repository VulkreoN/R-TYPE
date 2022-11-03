#ifndef COLLIDE_SYSTEM_HPP
#define COLLIDE_SYSTEM_HPP

#include <vector>
#include "ISystem.hpp"
#include "IEntity.hpp"
#include "Position.hpp"
#include "Nono.hpp"

namespace R_TYPE {

    class CollideSystem: public ISystem {
        public:
            CollideSystem();
            ~CollideSystem();

            void init(SceneManager &sceneManager) final;
            void update(SceneManager &sceneManager, uint64_t deltaTime) final;
            void destroy() final;

            static bool canMove(Position pos, SceneManager &sceneManger, Position toCheck);

            void didHitPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> project);
            void collideEnnemyPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player);
            void collideBonusPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player);
            void collideNonoPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player);
            void didHitEnnemi(SceneManager &sceneManager, std::shared_ptr<IEntity> project);
            void didHitProj(SceneManager &sceneManager, std::shared_ptr<IEntity> project);
            void didHitWall(SceneManager &sceneManager, std::shared_ptr<IEntity> project);
            void addUpddateNono(SceneManager &sceneManager, std::shared_ptr<IEntity> player);
            static bool isBlack(Position pos, sf::FloatRect box);
        
        private:
            std::vector<std::shared_ptr<IEntity>> _collidables2D;
    };
}

#endif