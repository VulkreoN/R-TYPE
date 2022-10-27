/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** Player
*/

#include "Player.hpp"

namespace R_TYPE {
    Player::Player(Position position): Component(Component::Type::PLAYER),
    _id(0), _pos(position), _attacking(false), _alive(true)
    {
        _spritesheet = std::make_unique<Sprite>("assets/player/player.png", _pos, 0, sf::IntRect(66, 0, 32, 12));
    }

    Player::~Player()
    {
    }

    void Player::setPosition(sf::Vector2f pos)
    {
        _pos = Position(pos);
    }

    sf::Vector2f Player::getPosition()
    {
        return _pos.getPosition();
    }

    sf::Sprite &Player::getSprite() const
    {
        return _spritesheet->getSprite();
    }

    bool Player::isAlive() const
    {
        return _alive;
    }

    bool Player::isAttacking() const
    {
        return _attacking;
    }

    void Player::setAlive(bool alive)
    {
        _alive = alive;
    }

    void Player::setAttacking(bool attacking)
    {
        _attacking = attacking;
    }
}
