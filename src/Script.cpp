#include "Script.hpp"
#include <iostream>

namespace R_TYPE {

    bool Script::turretScript(int distance, Position selfPos)
    {
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (CurrentFrame.asSeconds() > 5) {
            std::cout << "Turret shoot dans la direction du joueur " << std::endl;
            std::cout << "distance " << distance << std::endl;
            clock.restart();
            return (true);
        }
        return (false);
    }

    void Script::jorydeScript()
    {
        lastFrame = CurrentFrame;
        CurrentFrame = clock.getElapsedTime();

        if (CurrentFrame.asSeconds() > 2) {
            std::cout << "Joryde laser dans la direction du joueur" << std::endl;
            clock.restart();
        }
    }
}