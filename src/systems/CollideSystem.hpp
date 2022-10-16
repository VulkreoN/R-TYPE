#ifndef COLLIDE_SYSTEM_HPP
#define COLLIDE_SYSTEM_HPP

#include <vector>
#include "ISystem.hpp"
#include "IEntity.hpp"
#include "Position.hpp"

namespace R_TYPE {

    class CollideSystem: public ISystem {
        public:
            CollideSystem();
            ~CollideSystem();

            void init(SceneManager &sceneManager) final;
            void update(SceneManager &sceneManager, uint64_t deltaTime) final;
            void destroy() final;

            static bool canMoveLeft(Position pos, SceneManager &sceneManger);
            static bool canMoveRight(Position pos, SceneManager &sceneManger);
            static bool canMoveUp(Position pos, SceneManager &sceneManger);
            static bool canMoveDown(Position pos, SceneManager &sceneManger);

            void didHitPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> project);
            void didHitEnnemi(SceneManager &sceneManager, std::shared_ptr<IEntity> project);
            static bool isBlack(Position pos);
        
        private:
            std::vector<std::shared_ptr<IEntity>> _collidables2D;
    };
}

#endif