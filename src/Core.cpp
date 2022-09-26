#include "Core.hpp"
#include "GameSystem.hpp"
#include "EventSystem.hpp"
#include "GraphicSystem.hpp"
#include <iostream>

namespace R_TYPE {

    Core::Core()
    {
        std::cout << "Core init\n";
        _systems[SystemType::GAME] = std::make_unique<GameSystem>();
        _systems[SystemType::EVENT] = std::make_unique<EventSystem>();
        _systems[SystemType::GRAPHIC] = std::make_unique<GraphicSystem>();
    }

    Core::~Core()
    {
        for (auto &system : _systems)
            system.second->destroy();
    }

    void Core::mainLoop()
    {
        for (auto &system : _systems)
            system.second->init(_sceneManager);
        std::cout << "boucle inf ma gueule\n";
        while (!_sceneManager.getShouldClose()) {
            for (auto &system : _systems)
            system.second->update(_sceneManager, 17);
        }
    }
}