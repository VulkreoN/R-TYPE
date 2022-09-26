/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** EventSystem
*/

#include "EventSystem.hpp"
#include <iostream>

namespace R_TYPE {
    EventSystem::EventSystem()
    {
        std::cout << "Event System create" << std::endl;
    }

    EventSystem::~EventSystem()
    {
    }

    void EventSystem::init(SceneManager &manager)
    {
        std::cout << "Event System init" << std::endl;
    }

    void EventSystem::update(SceneManager &manager, uint64_t deltaTime)
    {
        std::cout << "Event System update" << std::endl;
    }

    void EventSystem::destroy()
    {
        std::cout << "Event System destroyed" << std::endl;
    }
}