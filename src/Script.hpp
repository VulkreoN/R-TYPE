#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <SFML/Graphics.hpp>
#include "Position.hpp"

namespace R_TYPE {

    class Script {
        public: 

        bool turretScript(Position selfPos);
            void jorydeScript();
        private:
            sf::Clock clock;
            sf::Time lastFrame;
            sf::Time CurrentFrame;
    };
}

#endif