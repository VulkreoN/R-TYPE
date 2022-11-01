/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** AnimationManager
*/

#include "AnimationManager.hpp"

namespace R_TYPE {

    void AnimationManager::playAnim(Animation anim)
    {
        if (anim.getDoActions() == false)
            anim.setRect(sf::IntRect(anim.getX() * anim.getRect().width,anim.getY() * anim.getRect().height,anim.getRect().width,anim.getRect().height));
        else {
            while (clock) {
                int i = anim.getX();
                anim.setRect(sf::IntRect(i * anim.getRect().width,anim.getY() * anim.getRect().height,anim.getRect().width,anim.getRect().height));
                if (i > anim.getXmax())
                    i = anim.getX();
            }

        }
    }
}