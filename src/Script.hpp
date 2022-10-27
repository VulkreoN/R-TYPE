#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Velocity.hpp"

namespace R_TYPE {

    class Script {
        public: 

        bool turretScript();
        bool jorydeScript(sf::Vector2f distance, std::shared_ptr<R_TYPE::Velocity> selfVel);
        bool robotScript(sf::Vector2f distance, std::shared_ptr<R_TYPE::Velocity> selfVel);
        void spatialScript(std::shared_ptr<R_TYPE::Velocity> selfVel);
        private:
            sf::Clock clock;
            sf::Time lastFrame;
            sf::Time CurrentFrame;
    };
}

#endif