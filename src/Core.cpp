#include <iostream>
#include <chrono>
#include <thread>
#include "Core.hpp"
#include "GameSystem.hpp"
#include "EventSystem.hpp"
#include "GraphicSystem.hpp"
#include "CollideSystem.hpp"
#include "ServerSystem.hpp"
#include "ClientSystem.hpp"

namespace R_TYPE {

    bool Core::isServeur;

    Core::Core(size_t port)
    {
        std::cout << "Core init\n";
        isServeur = true;
        _systems[SystemType::GAME] = std::make_unique<GameSystem>();
        // _systems[SystemType::EVENT] = std::make_unique<EventSystem>();
        _systems[SystemType::COLLIDE] = std::make_unique<CollideSystem>();
        _systems[SystemType::NETWORK] = std::make_unique<ServerSystem>(port);
    }

    Core::Core(std::string ip, size_t port)
    {
        std::cout << "Core init\n";
        isServeur = false;
        _systems[SystemType::GAME] = std::make_unique<GameSystem>();
        //_systems[SystemType::GRAPHIC] = std::make_unique<GraphicSystem>();
        // _systems[SystemType::EVENT] = std::make_unique<EventSystem>();
        // _systems[SystemType::COLLIDE] = std::make_unique<CollideSystem>();
        _systems[SystemType::NETWORK] = std::make_unique<ClientSystem>(ip, port);
    }

    Core::~Core()
    {
        for (auto &system : _systems)
            system.second->destroy();
    }

    void Core::mainLoop()
    {
        auto clock = std::chrono::high_resolution_clock::now();

        for (auto &system : _systems)
            system.second->init(_sceneManager);
        while (!_sceneManager.getShouldClose()) {
            auto time = std::chrono::high_resolution_clock::now();
            auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(time - clock).count();
            if (deltaTime < UPDATE_DELTA) {
                std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_DELTA - deltaTime));
                continue;
            }
            for (auto &system : _systems) {
                system.second->update(_sceneManager, deltaTime);
                clock = time;
            }
        }
    }
}
