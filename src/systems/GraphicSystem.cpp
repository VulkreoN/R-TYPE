/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** GraphicSystem
*/

#include "GraphicSystem.hpp"
#include <iostream>

namespace R_TYPE {
    GraphicSystem::GraphicSystem()
    {
        std::cout << "Graphic System create" << std::endl;
    }

    GraphicSystem::~GraphicSystem()
    {
    }

    void GraphicSystem::init(SceneManager &manager)
    {
        std::cout << "Graphic System init" << std::endl;
    }

    void GraphicSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        std::cout << "Graphic System update" << std::endl;
    }

    void GraphicSystem::destroy()
    {
        std::cout << "Graphic System destroyed" << std::endl;
    }
}