/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** AnimationManager
*/

#include "AnimationManager.hpp"
#include <iostream>

namespace R_TYPE {

    void AnimationManager::playAnim(std::shared_ptr<Animation> anim, std::shared_ptr<Sprite> sprite)
    {
        if (anim->getDoActions() == false) {
            anim->setRect(sf::IntRect(anim->getX() * anim->getRect().width, anim->getY() * anim->getRect().height, anim->getRect().width,anim->getRect().height));
            sprite->setRect(anim->getRect());
        } else {
            anim->setCurrentFrame(anim->getClock().getElapsedTime());
            if (anim->getCurrentFrame().asSeconds() > 0.1) {
                anim->setRect(sf::IntRect(anim->getNbFrame() * anim->getRect().width + anim->getPosX() - anim->getRect().width,anim->getY() * anim->getRect().height + anim->getPosY(),anim->getRect().width,anim->getRect().height));
                if (anim->getNbFrame() >= anim->getXmax())
                    anim->setNbFrame(anim->getX());
                anim->setNbFrame(anim->getNbFrame() + 1);
                sprite->setRect(anim->getRect());
                anim->restartClock();
            }
        }
    }

    void AnimationManager::update_player(std::shared_ptr<IEntity> &e, uint64_t deltaTime)
    {
        auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
        auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
        auto anims = e->getFilteredComponents(IComponent::Type::ANIMATION);
        for (int i = 0; i < anims.size(); i++) {
            auto anim_cast = Component::castComponent<Animation>(anims[i]);
            if (anim_cast->getState() == player->getState())
                playAnim(anim_cast, sprite);
        }
    }

    void AnimationManager::update_ennemy(std::shared_ptr<IEntity> &e, uint64_t deltaTime)
    {
        auto ennemy = Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]);
        auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
        auto anims = e->getFilteredComponents(IComponent::Type::ANIMATION);
        for (int i = 0; i < anims.size(); i++) {
            auto anim_cast = Component::castComponent<Animation>(anims[i]);
            if (anim_cast->getState() == ennemy->getState()) {
                playAnim(anim_cast, sprite);
            }
        }
    }

    void AnimationManager::update_nono(std::shared_ptr<IEntity> &e, uint64_t deltaTime)
    {
        auto nono = Component::castComponent<Nono>((*e)[IComponent::Type::NONO]);
        auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
        auto anims = e->getFilteredComponents(IComponent::Type::ANIMATION);
        for (int i = 0; i < anims.size(); i++) {
            auto anim_cast = Component::castComponent<Animation>(anims[i]);
            if (anim_cast->getState() == nono->getState()) {
                playAnim(anim_cast, sprite);
            }
        }
    }

    //void AnimationManager::update_projectile(std::shared_ptr<IEntity> &e, uint64_t deltaTime)
    //{
    //    for (auto &e : manager.getCurrentScene()[IEntity::Tags::ANIMATED]) {
    //        auto anim = Component::castComponent<Animation>((*e)[IComponent::Type::ANIMATION]);
    //        if (anim->getState() == (*e))
    //    }
    //}
}