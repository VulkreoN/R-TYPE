/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GameSystem
*/

#include "GameSystem.hpp"

namespace R_TYPE {
    GameSystem::GameSystem()
    {
        std::cout << "Game System create" << std::endl;
    }

    GameSystem::~GameSystem()
    {
    }

    void GameSystem::init(SceneManager &manager)
    {
        std::cout << "Game System init" << std::endl;
    }

    void GameSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        std::cout << "Game System update" << std::endl;
    }

    void GameSystem::destroy()
    {
        std::cout << "Game System destroyed" << std::endl;
    }
}