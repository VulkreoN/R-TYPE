/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** AnimationManager
*/

#ifndef ANIMATIONMANAGER_HPP_
#define ANIMATIONMANAGER_HPP_

#include "Animation.hpp"
#include "SceneManager.hpp"
#include "Player.hpp"
#include "Ennemy.hpp"
#include "Nono.hpp"
#include "Projectiles.hpp"
#include <memory>

namespace R_TYPE {
    class AnimationManager {
        public:

            void playAnim(std::shared_ptr<Animation> anim, std::shared_ptr<Sprite> sprite);
            void update_player(std::shared_ptr<IEntity> &e, uint64_t deltaTime);
            bool update_ennemy(std::shared_ptr<IEntity> &e, uint64_t deltaTime);
            void update_projectile(std::shared_ptr<IEntity> &e, uint64_t deltaTime);
            void update_nono(std::shared_ptr<IEntity> &e, uint64_t deltaTime);

        protected:
        private:
    };
}
#endif /* !ANIMATIONMANAGER_HPP_ */
