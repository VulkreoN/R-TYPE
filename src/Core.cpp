#include "Core.hpp"
#include <iostream>

namespace R_TYPE {

    Core::Core()
    {
        std::cout << "Core init\n";
        std::cout << "Create System here\n";
    }

    Core::~Core()
    {
        std::cout << "Core deleted\n";
    }

    void Core::mainLoop()
    {
        std::cout << "Init system here\n";
        std::cout << "boucle inf ma gueule\n";
        // while (!_sceneManager.getShouldClose()) {
        // }
        std::cout << "Destroy system here\n";
    }
}